#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
#include "Task.h"
#include "BinaryHeap.h"
#include "FibonacciHeap.h"


std::vector<std::string> taskNames = {
        "Finish Calculus Homework",
        "Do Laundry",
        "Go to the gym",
        "Send Applications",
        "Update Resume",
        "Call Parents",
        "Work on Group Project",
        "Watch Lecture",
        "Update LinkedIn Profile",
        "Cook Dinner",
        "Reserve Study Room at Library",
        "Practice Coding Interview Problems",
        "Submit Late Assignment Request",
        "Attend Club Meeting",
        "Renew Parking Pass",
        "Volunteer at Campus Event",
        "Go to Office Hours",
        "Take Out Trash",
        "Refill Coffee Maker",
        "Build Portfolio Website",
        "Pick Up Packages from Mailroom",
        "Meal Prep for the Week",
        "Schedule Advising Appointment",
        "Check Grades on Canvas",
        "Fix Compilation Errors",
        "Submit Scholarship Application",
        "Study for Physics Exam",
        "Write English Essay",
        "Review Lecture Notes",
        "Submit Programming Assignment",
        "Finish MATLAB Problem Set",
        "Finish Practice Midterm",
        "Take Online Quiz",
        "Read Article for Discussion",
        "Record Presentation Video",
        "Finish Discussion Post",
        "Buy Coffee Before Class",
        "Pay Housing Bill",
        "Sign Up for Career Fair",
        "Go to Financial Aid Office",
        "Participate in Hackathon",
        "Create Data Visualization",
        "Start Personal Project",
        "Write Cover Letter",
        "Make Breakfast",
        "Go for a Run",
        "Walk the Dog",
        "Set Alarm for Morning Class",
        "Pay Utility Bill",
        "Prepare for Job Interview",
        "Practice Elevator Pitch",
        "Clean Up Desktop Files",
        "Update To-Do List",
        "Attend Guest Lecture",
        "Write Reflection Paper",
        "Debug Project Code",
        "Email Professor About Grade"
    };

BinaryHeap bh;
FibonacciHeap fh;

void buildBinary()
{
    for (int i = 0; i < 100000; i++)
    {

        int randomNum = rand() % 56;
        bh.insert(Task (i, taskNames[randomNum], i));
    }
}

void buildFibonacci()
{
    for (int i = 0; i < 100000; i++)
    {

        int randomNum = rand() % 56;
        fh.insertTask(Task (i, taskNames[randomNum], i));
    }
}

int main()
{

    std::cout << "PRIORITY SCHEDULER SIMULATION -- BINARY HEAP VS FIBONACCI HEAP" << std::endl;





    srand(static_cast<unsigned int>(time(NULL)));

    auto t1 = std::chrono::steady_clock::now();
    buildBinary();
    auto t2 = std::chrono::steady_clock::now();
    auto t3 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);


    std::cout << std::endl;

    srand(static_cast<unsigned int>(time(NULL)));

    auto startFib = std::chrono::steady_clock::now();
    buildFibonacci();
    auto endFib = std::chrono::steady_clock::now();
    auto fibDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endFib - startFib);

    std::cout << "=== Build Comparison (100,000 Insert Operations) ===" << std::endl;
    std::cout << "Fibonacci Heap:     " << fibDuration.count() << "ms" << std::endl;
    std::cout << "Binary Heap:        " << t3.count() << "ms\n" << std::endl;


    while(true)
    {
        int selection;
        std::cout << "\nPlease Make a Selection:" << std::endl;
        std::cout << "1) View Top 10 Highest-Priority Tasks" << std::endl;
        std::cout << "2) Search for a Specific Task by ID" << std::endl;
        std::cout << "3) Quit" << std::endl;
        std::cin >> selection;

        if (selection == 1)
        {
            std::cout << "Binary Heap -- 10 Highest-Priority Tasks:\n" << std::endl;

            auto t4 = std::chrono::steady_clock::now();
            for (int i = 0; i < 10; i++)
            {
                Task t = bh.getTop();
                std::cout << "Priority: " << t.priority << " ID: " << t.id << " Task Name: " << t.name << std::endl;
                bh.pop();
            }
            auto t5 = std::chrono::steady_clock::now();
            auto t6 = std::chrono::duration_cast<std::chrono::milliseconds>(t5 - t4);
            std::cout << "Binary Heap took " << t6.count() << "ms\n" << std::endl;


            std::cout << "\nFibonacci Heap -- 10 Highest-Priority Tasks:\n" << std::endl;

            auto t7 = std::chrono::steady_clock::now();
            for (int i = 0; i < 10; i++)
            {
                Task t = fh.extractHighestPriority();
                std::cout << "Priority: " << t.priority << " ID: " << t.id << " Task Name: " << t.name << std::endl;
            }
            auto t8 = std::chrono::steady_clock::now();
            auto t9 = std::chrono::duration_cast<std::chrono::milliseconds>(t8 - t7);
            std::cout << "Fibonacci Heap took " << t9.count() << "ms" << std::endl;
        }

        else if (selection == 2)
        {
            int Id;
            std::cout << "Enter an ID to Search For (1-100,000)" << std::endl;
            std::cin >> Id;

            std::cout << "\nBinary Heap Search: " << std::endl;

            auto t10 = std::chrono::steady_clock::now();
            const Task* tbh = bh.findById(Id);
            auto t11 = std::chrono::steady_clock::now();
            auto t12 = std::chrono::duration_cast<std::chrono::milliseconds>(t11 - t10);

            std::cout << "\nTask with ID " << Id << " --- Name: " << tbh->name << " Priority: " << tbh->priority <<  std::endl;
            std::cout << "Binary Heap took " << t12.count() << "ms" << std::endl;


            std::cout << "\nFibonacci Heap Search: " << std::endl;

            auto t13 = std::chrono::steady_clock::now();
            const Task* tfh = fh.findById(Id);
            auto t14 = std::chrono::steady_clock::now();
            auto t15 = std::chrono::duration_cast<std::chrono::milliseconds>(t14 - t13);

            std::cout << "\nTask with ID " << Id << " --- Name: " << tfh->name << " Priority: " << tfh->priority <<  std::endl;
            std::cout << "Fibonacci Heap took " << t15.count() << "ms" << std::endl;
        }

        else break;
    }






    return 0;
}

