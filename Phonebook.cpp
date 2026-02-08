#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <limits>
using namespace std;

class User {
   private:
   string location = "unset";
   public:
   string username,email;
   map<string, string>skills;

   User(string n="",string e=""):username(n),email(e)  {}

   string getUsername() const {
    return username;
   }
   
   string getEmail() const {
    return email;
   }

   string getLocation() const {
    return location;
   }
   
   void setLocation(string l) {
        location = l;
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

        cout<<"The list of skills that have the level ' "<<filterLevel<<" ' is listed below.\n\n";
        for(auto i:skills) {
            if (i.second == filterLevel) {
                cout<<"Skill: "<<i.first<<"    Level: "<<i.second<<"\n\n";
            }
        }
    } else {
        cout<<"Here is all the skills and their corresponding levels:\n";

        for(auto i:skills) {
          cout<<i.first<<": "<<i.second<<"\n";
        }
      }
   }

   void clearSkill(string s) {

    if(skills.erase(s)) {
        cout<<"Skill deleted succesfully!!\n\n";
    } else cout<<"Skill not found!! Please try again.\n\n";

   }

   void editSkill() {

    if(skills.empty()) {
        cout<<"You have no skills to edit!!\n\n";
        return;
    }

    int counter = 1;
    vector<string> skillNames;
    
    for(auto pair : skills) {
        cout<<counter<<". "<<"Skill: "<<pair.first<<"    Level: "<<pair.second<<"\n";
        counter++;
        
        skillNames.push_back(pair.first);
    }

    int skillnum;
    string newLevel;

    cout<<"\nPlease enter the number of the skill you want to edit: ";
    cin>>skillnum;

    if(skillnum < 1 || skillnum > skillNames.size()) {
        cout<<"Invalid choice! Please enter a number between 1 and "<<skillNames.size()<<".\n\n";
        return;
    }

    cout<<"Please enter the new level for the skill (Beginner, Intermediate or Advanced): ";
    cin>>newLevel;

    storeSkills(skillNames[skillnum - 1], newLevel);

    cout<<"Your skill level has been edited succesfully!!\n\n";

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
    cout<<"\nThe salary according to your skills and their levels: "<<salary<<"\n\n";
   }

   void saveSkills(ofstream& file) const {
    for(const auto& pair : skills) {
        file << "SKILL " << pair.first << " " << pair.second << endl;
    }
   }

};

int findUserIndex(const vector<User>& users, const string& username) {
    for( int i = 0; i<users.size(); i++) {
        if(users[i].username == username) {
            return i;
        }    
    }
    return -1;
}

void savetofile(const vector<User>& users) {
    ofstream file("data.txt");

    for(const auto& user : users) {
        file << "USER " << user.getUsername() << " "
        << user.getEmail() << " "
        << user.getLocation() << endl;

        user.saveSkills(file);

        file << "ENDUSER" << endl;
    }

    file.close();
}

void loadfromfile(vector<User>& users) {
    ifstream file("data.txt");
    if (!file) return;

    string word;
    while (file >> word) {
        if(word == "USER") {
            string username,email,location;
            file >> username >> email >> location;

            User u(username,email);
            u.setLocation(location);

            while (file >> word) {
                if (word == "ENDUSER") {
                    break;
                }

                if (word == "SKILL") {
                    string skill,level;
                    file >> skill >> level;
                    u.storeSkills(skill,level);
                }
            }

            users.push_back(u);
        }
    }

    file.close();
}

int main() {
    string username,email,location;
    int num = 1;

    vector <User> users;
    loadfromfile(users);

    while(num!=6) {
      cout<<"------Menu------\n"
      <<"1. Register a new user\n"
      <<"2. Add new skills\n"
      <<"3. Show user info\n"
      <<"4. Delete a skill\n"
      <<"5. Edit skill level\n"
      <<"6. Exit the application\n";

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
            
            int index = findUserIndex(users, username);
            
            if (index != -1) {
                cout << "Username already exists!\n\n";
                break;
            }
            
            users.push_back(User(username, email));
            users.back().setLocation(location);
            
            cout<<"\nYour process was completed succesfully!!\n\n";
            
            break;
          }

          case 2: {
            int skillnum;
            string Skill,level,username;
            
            cout<<"Enter your username to add skills: ";
            cin>>username;
            
            int index = findUserIndex(users, username);
            
            if (index == -1) {
                cout << "User not found!\n";
                break;
            }
            
            cout<<"\nHow many skills will you enter: ";
            cin>>skillnum;
            
            cout<<"Please enter the skill/s and their corresponding level (Beginner,Intermediate,Advanced) here:\n";
            
            for(int i=0;i<skillnum;i++) {
                cout<<"Skill "<<i+1<<": ";
                cin>>Skill;
                cout<<"Level: ";
                cin>>level;
                
                users[index].storeSkills(Skill,level);
            }
            
            cout<<"Your skills have been added succesfully!!\n\n";
            break;
          }

          case 3: {

            string username;
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"\nEnter your username: ";
            cin>>username;

            int index = findUserIndex(users, username);
            
            if (index == -1) {
                cout << "User not found!\n\n";
                break;
            }

            cout<<"\n\nHere is your registration info:\n";
            users[index].info();
            cout<<endl;

            users[index].showSkills();
            users[index].calculateSalary();

          break;
          }

          case 4: {
            
            int deletedskillnum,counter = 1;
            string skill,username;
            
            cout<<"Enter your username to delete skills: ";
            cin>>username;
            
            int index = findUserIndex(users, username);
            
            if (index == -1) {
                cout << "User not found!\n\n";
                break;
            }
            
            if (users[index].skills.empty()) {
                cout << "You have no skills to delete!\n\n";
                break;
            }

            vector<string> skillNames;

            for(auto i:users[index].skills) {
                cout<<counter<<". "<<"Skill: "<<i.first<<"    Level: "<<i.second<<"\n";
                counter++;

                skillNames.push_back(i.first);
            }

            cout<<"\nPlease enter the number of the skill you want to delete: ";
            cin>>deletedskillnum;

            if(deletedskillnum < 1 || deletedskillnum > skillNames.size()) {
                cout<<"Invalid choice! Please enter a number between 1 and "<<skillNames.size()<<".\n\n";
                break;
            }

            users[index].clearSkill(skillNames[deletedskillnum - 1]);
            
            break;
          }

          case 5: {
            string username;

            cout<<"Enter your username to edit skill level: ";
            cin>>username;

            int index = findUserIndex(users, username);
            
            if (index == -1) {
                cout << "User not found!\n\n";
                break;
            }

            users[index].editSkill();

            break;

          }
          case 6: {
          cout<<"\nYou have chosen to exit the application.\n\n";

          savetofile(users);
          
          break;
          }

          default:
          cout<<"Invalid choice! Please enter an integer number between 1 and 6.\n";
      }
    }
}