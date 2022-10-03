#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <fstream>

struct Computer
{
    int id;
};

struct User{
    int id;
    std::string name;
    std::list<int> friends = {};
};

class Server
{
private:
    class AuthorisationsLog
    {
    public:
        int get_user_id_by_computer(Computer computer)
        {
            /*
            Return user id if computer in log
            Return -1 if else
            */
            std::string line;
            std::ifstream file("OnServer/AuthorisationsLog.txt", std::ios::app);
            if (file.is_open())
                while (std::getline(file, line))
                {
                    if (line.find(std::to_string(computer.id)) == 0)
                    {
                        file.close();
                        return std::stoi(line.substr(line.find(' ') + 1));
                    }
                }
            file.close();
            return -1;
        }
        void new_record(Computer computer, int user_id)
        {
            std::ofstream file("OnServer/AuthorisationsLog.txt", std::ios::app);
            if (file.is_open())
                file << computer.id << " " << user_id << std::endl;
            file.close();
        }
    };

    bool is_true_passwd(int user_id, std::string passwd)
    {
        std::string line;
        std::ifstream file("0.txt");
        if (file.is_open())
        {
            std::getline(file, line); // name
            std::getline(file, line); // passwd
            return passwd == line;
        }
        file.close();
        return false;
    }
    AuthorisationsLog authorisation_log;

public:
    void authorisation(Computer computer, int id, std::string passwd)
    {
        if (is_true_passwd(id, passwd))
            authorisation_log.new_record(computer, id);
    }

    User get_user_by_computer(Computer computer)
    {
        int user_id = authorisation_log.get_user_id_by_computer(computer);
        if (user_id == -1)
        {
            User user;
            user.id = -1;
            user.name = "visitor";
            return user;
        }
        User user;
        std::string line;
        std::ifstream file("OnServer/users/" + std::to_string(user_id) + ".txt", std::ios::app);
        if (file.is_open())
        {
            std::getline(file, line); // name
            user.name = line;
            std::getline(file, line); // passwd
            while (std::getline(file, line))
                user.friends.push_back(std::stoi(line)); // friend id
        }
        file.close();
        return user;
    }
};

void router(std::string command)
{
    if (command == "authorise"){}
    else if (command == "-h"){
        std::cout << "You are in social network consol, my autors are Dmitry Sergeevich and vorobushek, good luck" << std::endl;
    }
    else{
        std::cout << "no command " << command << std::endl;
    }
}

int main()
{
    Computer my_computer;
    my_computer.id = 0;
    Server server;

    User me = server.get_user_by_computer(my_computer);
    
    // server.authorisation(my_computer, 0, "123123123");
    // me.save_at_computer();

    std::string command = "-h";
    while (command!="exit"){
        router(command);
        std::cout << me.name << "> ";
        std::cin >> command;
    }
    return 0;
}
