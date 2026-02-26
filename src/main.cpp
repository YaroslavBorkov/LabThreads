#include "blocking_queue.hpp"
#include "contact.hpp"
#include "parser.hpp"
#include "writer.hpp"

#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
#include <unordered_map>

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Usage: lab2_3mod <input.txt> <output.txt> [workers count]\n";
        return 0;
    }

    std::string input = argv[1];
    std::string output = argv[2];

    int workers = 4; //кол-во рабочих потоков по умолчанию 4
    if (argc >= 4) workers = std::stoi(argv[3]);
    if (workers <= 0) workers = 4;

    BlockingQueue<Task> tasks; 
    BlockingQueue<Result> results;

    std::thread producer([&] {
        std::ifstream in(input);
        std::string line;
        while (std::getline(in, line)) {
            Contact c;
            if (parse_contact_line(line, c)) tasks.push(Task{false, std::move(c)});
        }
        for (int i = 0; i < workers; i++) tasks.push(Task{true, {}});   
    });

    std::vector<std::thread> pool; 
    //пул рабочих потоков, которые будут обрабатывать контакты и распределять их по корзинам (buckets)
    for (int i = 0; i < workers; i++) {
        pool.emplace_back([&] { 
            //emplace_back - добавляет новый элемент в конец вектора, конструируя его на месте,
            // без необходимости копирования или перемещения существующих элементов
            while (true) {
                Task t = tasks.pop();
                if (t.stop) break;

                Result r;
                r.stop = false;
                r.key = bucket_key_ascii_lastname(t.c);
                r.c = std::move(t.c);
                results.push(std::move(r));
            }
            results.push(Result{true, '#', {}});
        });
    }

    std::unordered_map<char, std::vector<Contact>> buckets;
    std::thread aggregator([&] {
        int stops = 0;
        while (stops < workers) {
            Result r = results.pop();
            if (r.stop) stops++;
            else buckets[r.key].push_back(std::move(r.c));           
        }
        write_buckets_one_file(output, buckets);
    });

    producer.join();
    for (auto& t : pool) t.join();
    aggregator.join();

    std::cout << "Done. Output: " << output << "\n";
    return 0;
}
