#include<iostream>
#include<fstream>
#include<string>
#include<limits>
#include<cctype>

void add_Task();
void edit_Task();
void delete_Task();
int display_Tasks();
void show_Options();
void print_Border();
void filter_Tasks();

int main()
{
    int user_choice;
    std::cout << "Welcome to ToDoList...\nYou can do the following operations:"<< std::endl;
    while (true)
    {
        show_Options();
        print_Border();
        std::cout << "Which Operation do you want to perform ?\nNOTE: Enter the index of the operation:\n";
        std::cin>>user_choice;
        std::cin.clear();
        if (user_choice==6) break ;
        switch (user_choice)
        {
        case 1:
            display_Tasks();
            break;
        case 2:
            add_Task();
            break;
        case 3:
            edit_Task();
            break;
        case 4:
            filter_Tasks();
            break;
        case 5:
            delete_Task();
            break;
        default:
            std::cout << "Please provide input as per the instructions provided:"<< std::endl;
            break;
        }
    }
    print_Border();
    std::cout << "Thank You For using To Do List"<< std::endl;
    print_Border();
    return 0;
}
void add_Task(){
    std::string new_task;
    char user_choice;
    print_Border();
    while (true)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout<<"Enter the task that you want to add in.\nNote the task will be incompleted at the time of adding while you can change the state after the task is created."<< std::endl;
        std::getline(std::cin,new_task);
        if(!(new_task.empty())){
            std::cout<<new_task<<std::endl;
            std::ofstream out("todolist.txt",std::ios::app);
            if(out.is_open()){
                out<<new_task<<" (I)"<<std::endl;
                out.close();
                std::cout<<"Do You want to add more ?:(Y/N)"<<std::endl;
                std::cin>>user_choice;
                if(std::tolower(user_choice)=='n') break;
            }
            else{
                std::cout<<"There was problem occured , Please Try Again."<<std::endl;
            }
        }
        else
        {
            std::cout<<"Please provide input properly"<<std::endl;
        }
    }
    
}
void edit_Task(){
    print_Border();
    display_Tasks();
    int task_no,counter=0;
    std::string task;
    std::cout<<"Which Task Do You want to edit?(Enter the index of the respective task.)"<<std::endl;
    std::cin>>task_no;
    std::ifstream taskfile("todolist.txt");
    std::ofstream tempfile("tempfile.txt");
    counter += 1;
    while(std::getline(taskfile,task))
    {
        if (counter == task_no){
            int user_ans;
            std::cout<<"Do you want to edit the task name or completion status ?\n 1 for task name\n 2 for completion \n"<< std::endl;
            std::cin>> user_ans;
            if(user_ans==1)
            {
                std::string new_taskname;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Write down the name of task that you want "<< task << " to be changed into\n"<< std::endl;
                std::getline(std::cin, new_taskname);
                tempfile << new_taskname << " (I)"<< std::endl;
            }
            else if(user_ans==2)
            {
                char state_completion;
                std::cout << "What do you want to change the state of completion into:(C for completed I for imcomplete)"<< std::endl;
                std::cin>>state_completion;
                switch (std::toupper(state_completion)){
                    case 'C':
                        task[task.length()-2]='C';
                        tempfile << task << std::endl;
                        std::cout << "The state of completion was changed into completed."<<std::endl;
                        break;
                    case 'I':
                        task[task.length()-2]='I';
                        tempfile << task << std::endl;
                        std::cout << "The state of completion was changed into incomplete."<<std::endl;
                        break;
                    default:
                        std::cout<<"Your response was invalid"<<std::endl;
                }
            }
        }
        else
            {
                tempfile << task << std::endl;
            }
        counter ++;
    }
    taskfile.close();
    tempfile.close();
    std::remove("todolist.txt");
    std::rename("tempfile.txt","todolist.txt");
}
void delete_Task(){
    print_Border();
    display_Tasks();
    int task_no,counter=0;
    std::string task;
    print_Border();
    std::cout<<"Which Task Do You want to edit?(Enter the index of the respective task.)"<<std::endl;
    std::cin>>task_no;
    std::ifstream taskfile("todolist.txt");
    std::ofstream tempfile("tempfile.txt");
    counter += 1;
    while(std::getline(taskfile,task))
    {
        if (counter != task_no){
                tempfile << task << std::endl;
            }
        if (counter == task_no) std::cout << "The respective task was deleted successfully"<< std::endl;
        counter ++;
    }
    taskfile.close();
    tempfile.close();
    std::remove("todolist.txt");
    std::rename("tempfile.txt","todolist.txt");
}
int display_Tasks(){
    std::string task;
    int counter=0;
    print_Border();
    std::cout << "\t\t  Tasks"<<std::endl;
    print_Border();
    std::ifstream task_file("todolist.txt");
    if(!(std::getline(task_file,task))) std::cout << "There are currently no items in To Do List"<< std::endl;
    while(std::getline(task_file,task)){
        std::cout << ++counter << ". "<<task<<std::endl;
    }
    
    task_file.close();

    return 0;
}
void filter_Tasks()
{
    print_Border();
    std::cout << "You want the tasks that are complete or incomplete?(C for completed tasks while I for incomplete tasks)" << std::endl;
    char user_want;
    std::string task;
    std::cin>>user_want;
    print_Border();
    int counter=0;
    if((std::toupper(user_want))=='C'){
        std::ifstream task_file("todolist.txt");
        while(std::getline(task_file,task)){
            if((task[(task.length()-2)])=='C') std::cout<<++counter<<". "<<task<<std::endl;
        }
        task_file.close();
    }
    else if((std::toupper(user_want))=='I'){
        std::ifstream task_file("todolist.txt");
        while(std::getline(task_file,task)){
            if((task[(task.length()-2)])=='I') std::cout<<++counter<<". "<<task<<std::endl;
        }
        task_file.close();
    }
    else{
        std::cout << "Please provide the input according to the instructions provided"<<std::endl;
    }
    print_Border();
     
}
void show_Options(){
    print_Border();
    std::cout << "1. View All The Tasks \n2. Add a Task \n3. Edit a Task \n4. View By Filtering Tasks(Based On Completion)\n5. Delete a Task \n6. Exit" << std::endl;
}
void print_Border(){
    std::cout<<"-------------------------------------------------\n"<<std::endl;
}