#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "gtest/gtest.h"

class Database {
public:
    virtual int get_population(const std::string& name) = 0;
};

class SingletonDatabase : public Database {
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
        //instance_count++;
    }

    std::map<std::string, int> populations;

public:
    //static int instance_count;

    /* Remove the copy and assignment constructors so that the
     * clients will not be able to construct objects in anyway.
     */
    SingletonDatabase(SingletonDatabase const&) = delete;
    void operator=(SingletonDatabase const&) = delete;

    static SingletonDatabase& get() {
        static SingletonDatabase db;
        return db;
    }

    int get_population(const std::string& name) override {
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

//int SingletonDatabase::instance_count = 0;

class DummyDatabase : public Database {
    std::map<std::string, int> populations;
public:

    DummyDatabase() {
        populations["alpha"] = 1;
        populations["beta"] = 2;
        populations["gamma"] = 3;
    }

    int get_population(const std::string& name) override {
        return populations[name];
    }
};

struct SingletonRecordFinder {
    int total_population(std::vector<std::string> names) {
        int result = 0;
        for (auto& name : names)
            result += SingletonDatabase::get().get_population(name);
        return result;
    }
};

struct ConfigurableRecordFinder {
    explicit ConfigurableRecordFinder(Database& db) : db{db}  {
    }

    int total_population(std::vector<std::string> names) const {
        int result = 0;
        for (auto& name : names)
            result += db.get_population(name);
        return result;
    }

    Database& db;
};

/*
 * Unit test for real database
 * Note that since this is implemented via singleton patterns,
 * changes to the database in a unit test environment cannot
 * be done in a test environment. Only integration tests are
 * possible for the original singleton objects.
 */
TEST(RecordFinderTests, SingletonTotalPopulationTest) {
    SingletonRecordFinder rf;
    std::vector<std::string> names{ "Mexico City", "Cairo" };
    int tp = rf.total_population(names);
    EXPECT_EQ(21671908 + 20484965, tp);
}

/* Use dependency injection to enable usage of a dummy database
 * for the purposes of unit testing
 */
TEST(RecordFinderTests, DependantTotalPopulationTest) {
    DummyDatabase db{};
    ConfigurableRecordFinder rf{ db };
    EXPECT_EQ(4, rf.total_population(
            std::vector<std::string>{"alpha", "gamma"}));
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
