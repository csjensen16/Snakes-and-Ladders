// Snakes and Ladders game

#include <iostream>
#include <ctime> // included to change random values each time
using namespace std;

// node structure for the board where players can move
struct node{
  int position;
  node *prev;
  node *next;
  node(int pos) : position(pos), prev(NULL), next(NULL){}
};

// player class where information and location of players are stored
class player{
  public:
    node *cu; // current position of player
    char name;
    int snakeheads; // for stats at end
    int bottomladdercounts; // for stats at end
    player(char c) : cu(NULL), name(c), snakeheads(0), bottomladdercounts(0){}
};

class board{
  private:
    node *head;
    node *tail;
    int sh[4] = {5, 7, 40, 45}; // location of snakeheads
    int st[4] = {0, 1, 4, 5}; // Location of stake tails
    int lb[3] = {9, 20, 41}; // location of ladder bottom
    int lt[3] = {31, 55, 90}; // Location of ladder tops
  public:
  // creates board from 0 - 99, done in class
    board(){
      head = tail = NULL;
      for(int i = 99; i >= 0; i--){
        insertatbeg(i);
      }
    }
    
    // used to create doubly linked list 
    void insertatbeg(int n){
      node *temp = new node(n);
      if(head == NULL){
        head = tail = temp;
        return;
      }
      temp -> next = head;
      head -> prev = temp;
      head = temp;
    }
    
    // used to move player forward and backwards
    void move(player &a){
      // starts cu at the beginning
      if(a.cu == NULL){
        a.cu = head;
      }
      
      int val = roll();
      cout << "-------------- Player " << a.name << "'s Turn --------------" << endl;
      cout << "Player " << a.name << " rolled a " << val << endl;
      // move the player forward the amount of the roll
      for(int i = 0; i < val && a.cu -> next != NULL; i++){
        a.cu = a.cu -> next;
      }
      cout << "Player " << a.name << "'s position is " << a.cu -> position << endl;
      //if the player reaches 99, then the player wins
      if(a.cu -> position >= 99){
        a.cu -> position = 99;
        return;
      }
      
      // for the amount of the snakes, check each
      for(int i = 0; i < 4; i++){
        if(a.cu -> position == sh[i]){
          cout << "Player " << a.name << " encountered a snake!" << endl;
          cout << a.name << " will go backwards to " << st[i] << endl;
          // sends player backwards to the snake tail
          while(a.cu -> position != st[i]){
            a.cu = a.cu -> prev;
          }
          // increase the snakeheads stat
          a.snakeheads++;
          cout << "Player " << a.name << "'s position is " << a.cu -> position << endl;
          return;
        }
      }
      // for the amount of ladders, check each
      for(int i = 0; i < 3; i++){
        if(a.cu -> position == lb[i]){
          cout << "Player " << a.name << " encountered a ladder!" << endl;
          cout << a.name << " will go forward to " << lt[i] << endl;
          // sends player forward to the ladder top
          while(a.cu -> position != lt[i]){
            a.cu = a.cu -> next;
          }
          // increase the bottomladdercounts stat
          a.bottomladdercounts++;
          cout << "Player " << a.name << "'s position is " << a.cu -> position << endl;
          return;
        }
      }
      
    }
    
    // random roll function
    int roll(){
      return 1 + rand() % 6;
    }
};


int main(){
  srand(time(0)); //included to make each run random
  cout << "*** Welcome to Snakes and Ladders! ***" << endl << endl;
  
  // creates two players
  player blue('B');
  player red('R');
  
  //creates board
  board sl;
  
  bool playing = true;
  while(playing){
    // call move function for blue
    sl.move(blue);
    // if blue is at 99 then blue wins
    if(blue.cu -> position == 99){
      cout << endl << "!!! Blue won !!!" << endl;
      playing = false;
      break;
    }
    // call move function for blue
    sl.move(red);
    // if red is at 99 then red wins
    if(red.cu -> position == 99){
      cout << endl << "!!! Red won !!!" << endl;
      playing = false;
      break;
    }
  }
  
  //print stats
  cout << endl;
  cout << "Player blue had " << blue.snakeheads << " snakehead encounters and ";
  cout << blue.bottomladdercounts << " ladder encounters. " << endl; 
  cout << "Blue ended at position " << blue.cu->position << endl << endl;
  
  cout << "Player red had " << red.snakeheads << " snakehead encounters and ";
  cout << red.bottomladdercounts << " ladder encounters. " << endl; 
  cout << "Red ended at position " << red.cu->position << endl;
  
  
  return 0;
}




