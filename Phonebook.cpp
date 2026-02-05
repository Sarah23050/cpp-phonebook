#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

class User {
   private:
   string location = "unset";
   public:
   string username,email;
   map<string, string>skills;

   User(string n="",string e=""):username(n),email(e)  {}

   void setLocation(string l) {
        location = l;
   }

   string getLocation() {
    return location;
   }

   void info() {
    cout<<"Username: "<<username<<"\nEmail: "<<email<<"\nLocation: "<<location<<endl;
   }

   void storeSkills(string skill, string level) {

    while(level != "Beginner" && level != "Intermediate" && level != "Advanced") {
       cout<<"Invalid level! Please enter the level as Beginner, Intermediate or Advanced only.\n";
       cin>>level;
    }

    skills[skill] = level;

   }

   void showSkills() {
    string filter;
    string filterLevel;

    cout<<"\nDo you want to filter the skills by the level that you choose? Please enter Yes or No: ";
    cin>>filter;

    if(filter == "Yes") {
        cout<<"Please enter the level: ";
        cin>>filterLevel;

        cout<<"The list of skills that have the level: "<<filterLevel<<" is listed below.\n\n";
        for(auto i:skills) {
            if (i.second == filterLevel) {
                cout<<"Skill: "<<i.first<<"    Level: "<<i.second<<"\n\n";
            }
        }
    } else {
        cout<<"Here is all the skills and levels:\n";

        for(auto i:skills) {
          cout<<i.first<<": "<<i.second<<"\n";
        }
      }
   }

   void clearSkill(string s) {

    if(skills.erase(s)) {
        cout<<"Skill deleted succesfully.\n\n";
    } else cout<<"Skill not found!! Please try again.\n\n";

   }
   
   void calculateSalary() {
    double salary = 0;
    
    for(auto i:skills){
        if(i.second == "Beginner") {
            salary += 1000;
        } else if(i.second == "Intermediate") {
            salary += 2000;
        } else if(i.second == "Advanced") {
            salary += 3000;
        }
    }
    cout<<"The salary according to your skills and their levels: "<<salary<<"\n\n";
   }
};

int main() {
    string username,email,location;
    int num = 1;
    vector <User> user;

    while(num!=5) {
      cout<<"1. Register a new user\n"
          <<"2. Add new skills\n"
          <<"3. Show user info\n"
          <<"4. Delete a skill\n"
          <<"5. Exit the application\n";

      cout<<"Enter your choice: ";
      cin>>num;
      
      switch(num) {
          case 1: {
        
          cout<<"\nEnter your username: ";
          cin>>username;
          cout<<"Enter your email address: ";
          cin>>email;
          cout<<"Enter your location: ";
          cin>>location;

          user = User(username,email);
          user.setLocation(location);

          cout<<"Your process was completed succesfully!!\n\n";

          break;
          }
          case 2: {
          int skillnum;
          string Skill,level;

          cout<<"\nHow many skills will you enter: ";
          cin>>skillnum;
          cout<<"Please enter the skill/s and the corresponding level (Beginner,Intermediate,Advanced) here:\n";

          for(int i=0;i<skillnum;i++) {
              cout<<"Skill "<<i+1<<": ";
              cin>>Skill;
              cout<<"Level: ";
              cin>>level;
              user.storeSkills(Skill,level);
          }
          break;
          }

          case 3: {

          cout<<"\n\nHere is your registration info:\n";
          user.info();
          cout<<endl;
          user.showSkills();
          user.calculateSalary();

          break;
          }

          case 4: {

          int deletedskills;
          string skill;

          cout<<"\nHow many skills would you like to delete: ";
          cin>>deletedskills;
          cout<<"Enter the skill/s you want to delete: ";

          for(int i=0;i<deletedskills;i++) {
              cin>>skill;
              user.clearSkill(skill);
          }

          break;
          }

          case 5: {
          cout<<"You have chosen to exit the application1.\n";
          break;
          }

          default:
          cout<<"Invalid choice! Please enter an integer number between 1 and 5.\n";
      }
    }
}