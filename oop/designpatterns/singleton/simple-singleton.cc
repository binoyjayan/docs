#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <boost/lexical_cast.hpp>

class SingletonDatabase {
    SingletonDatabase() {
        std::cout << "Initializing database" << std::endl;

        std::ifstream ifs("population.txt");

        std::string s, s2;
        while (getline(ifs, s)) {
            getline(ifs, s2);
            int pop = boost::lexical_cast<int>(s2);
            populations[s] = pop;
            // std::cout << s << ": " << populations[s] << std::endl;
        }
    }

    std::map<std::string, int> populations;

public:
    /* Remove the copy and assignment constructors so that the
     * clients will not be able to construct objects in anyway.
     */
    SingletonDatabase(SingletonDatabase const&) = delete;
    void operator=(SingletonDatabase const&) = delete;

    static SingletonDatabase& get() {
        static SingletonDatabase db;
        return db;
    }

    int get_population(const std::string& name) {
        return populations[name];
    }

    /*
    static SingletonDatabase* get_instance()
    {
      if (!instance)
        instance = new SingletonDatabase;
      return instance; // atexit
    }
    */
};

int main() {
    std::string city = "Tokyo";
    auto &db = SingletonDatabase::get();
    std::cout << "Population of " << city << " is "
              << db.get_population(city) << std::endl;
}


