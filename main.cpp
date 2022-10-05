#include <simplecpp>
#include "shooter.h"
#include "bubble.h"

/* Simulation Vars */
const double STEP_TIME = 0.02;

/* Game Vars */
const int PLAY_Y_HEIGHT = 450;
const int LEFT_MARGIN = 70;
const int TOP_MARGIN = 20;
const int BOTTOM_MARGIN = (PLAY_Y_HEIGHT+TOP_MARGIN);


void move_bullets(vector<Bullet> &bullets){
    // move all bullets
    for(unsigned int i=0; i<bullets.size(); i++){
                                      //check if bullet is in game window if not erase the bullet.

        if(!bullets[i].nextStep(STEP_TIME)){
            bullets.erase(bullets.begin()+i);
        }
    }
}

void move_bubbles(vector<Bubble> &bubbles){
    // move all bubbles
    for (unsigned int i=0; i < bubbles.size(); i++)
    {
        bubbles[i].nextStep(STEP_TIME);
    }
}
void small_bubbles(vector<Bubble> &bubbles, double x, double y, double radius){
    Color bubble_color = COLOR(255, 0, 180); //Creating bubble with some colour
    bubbles.push_back(Bubble(x, y, radius/2, -BUBBLE_DEFAULT_VX-50*3, 150, bubble_color));
    bubbles.push_back(Bubble(x, y, radius/2, BUBBLE_DEFAULT_VX+50*3, 150, bubble_color));

}

void collision(vector<Bubble> &bubbles,vector<Bullet> &bullets,int &score,int &false_score){
    // move all bubbles
    for (unsigned int i=0; i < bubbles.size(); i++)//Check for all bullets and bubbles using nested loop they are colliding or not
    {
       for (unsigned int j=0; j < bullets.size(); j++)
       {
       if((pow(bullets[j].get_center_x()- bubbles[i].get_center_x(),2)+pow(bullets[j].get_center_y()- bubbles[i].get_center_y(),2))
            < pow(bullets[j].get_height()/2 + bubbles[i].get_radius(),2 )){
         if (bubbles[i].get_radius() > BUBBLE_RADIUS_THRESHOLD){
                    score+=1;//increase score by 1.
                    false_score+=1;//increase false score by 1.
                    small_bubbles(bubbles, bubbles[i].get_center_x(), bubbles[i].get_center_y(), bubbles[i].get_radius());  // Create smaller bubbles when it collide
                    bubbles.erase(bubbles.begin()+i); bullets.erase(bullets.begin()+j); //Erase the bullet and bubble if they collide
                    }
         else{
            bullets.erase(bullets.begin()+j);bubbles.erase(bubbles.begin()+i);//Erase the bullet and bubble if they collide
            score+=1;//increase score by 1.
            false_score+=1;}//increase false score by 1.
       }
    }
}
}
void collision_with_shooter(vector<Bubble> &bubbles, Shooter &shooter, int &health,int &false_score){
     for (unsigned int i=0; i < bubbles.size(); i++)
     {//check for all the bubbles one by one that they collide or not with shooter
     if((pow(bubbles[i].get_center_x()-shooter.get_body_center_x(),2)+pow(bubbles[i].get_center_y()-shooter.get_body_center_y(),2))
         < pow(bubbles[i].get_radius()+23,2)){bubbles.erase(bubbles.begin()+i);//Erase the bubble who collides with shooter.
         health+=1;//Increase health count by 1
         false_score+=1;}//Increase false score by 1.
     }}
vector<Bubble> create_bubbles_level1()
{
    // create initial bubbles in the game for level 1
    vector<Bubble> bubbles;
    bubbles.push_back(Bubble(WINDOW_X/2.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, -BUBBLE_DEFAULT_VX, 150, COLOR(255,105,180)));
    bubbles.push_back(Bubble(WINDOW_X/4.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, BUBBLE_DEFAULT_VX, 150, COLOR(255,105,180)));
    bubbles.push_back(Bubble(WINDOW_X/2.0, BUBBLE_START_Y+20, BUBBLE_DEFAULT_RADIUS, 2*BUBBLE_DEFAULT_VX, 100, COLOR(255,105,180)));
    bubbles.push_back(Bubble(WINDOW_X/4.0, BUBBLE_START_Y+20, BUBBLE_DEFAULT_RADIUS, -2*BUBBLE_DEFAULT_VX, 100, COLOR(255,105,180)));
    return bubbles;
}
vector<Bubble> create_bubbles_level2()
{
    // create initial bubbles in the game for level 2
    vector<Bubble> bubbles;
    bubbles.push_back(Bubble(WINDOW_X/2.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, 2*BUBBLE_DEFAULT_VX, 100, COLOR(0,105,180)));
    bubbles.push_back(Bubble(WINDOW_X/4.0, BUBBLE_START_Y+20, 2*BUBBLE_DEFAULT_RADIUS, BUBBLE_DEFAULT_VX, 150, COLOR(255,0,180)));
    bubbles.push_back(Bubble(WINDOW_X/2.0, BUBBLE_START_Y+20, 2*BUBBLE_DEFAULT_RADIUS, -BUBBLE_DEFAULT_VX, 150, COLOR(255,0,180)));
    bubbles.push_back(Bubble(WINDOW_X/4.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, -2*BUBBLE_DEFAULT_VX, 100, COLOR(255,105,0)));
    return bubbles;
}

int main(){
int score=0,health=0,false_score=0;//Initiallise values for score,health,false_score. false score is the score ehich increases even if bubble hits shooter


    initCanvas("Bubble Trouble", WINDOW_X, WINDOW_Y);//Creating playing window
//getClick();

    Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);//Blue line
    b1.setColor(COLOR(0, 0, 255));

    string msg_health("Health:_/3");//Text showing health damaged out of 2.
    Text Health_Reamaining(WINDOW_X-LEFT_MARGIN, TOP_MARGIN, msg_health);

    string msg_level("LEVEL:_");//Text showing level NO.
    Text Level_No(WINDOW_X/2, TOP_MARGIN, msg_level);

    string msg_cmd("Cmd: _");//Text showing command which user had entered.
    Text charPressed(LEFT_MARGIN, BOTTOM_MARGIN, msg_cmd);

    string msg_score("score:_0");//Text showing score.0 is there at last because I want to show score in multiple of 10
    Text Score(WINDOW_X-LEFT_MARGIN, BOTTOM_MARGIN, msg_score);

    string msg_time("Time_Left:__");//text showing time left
    Text Time_Remaining(LEFT_MARGIN, TOP_MARGIN, msg_time);

    // Intialize the shooter
    Shooter shooter(SHOOTER_START_X, SHOOTER_START_Y, SHOOTER_VX);



    // Initialize the bullets (empty)
    vector<Bullet> bullets;

    XEvent event;

    // Main game loop
    if(false_score<4){
    // Initialize the bubbles
    vector<Bubble> bubbles = create_bubbles_level1();
     double seconds=0;
    while (false_score<4)// check if minimum 1 buuble of level 1 is there on screen for remaing in level 1
    {
        bool pendingEvent = checkEvent(event);
        if (pendingEvent)
        {
            // Get the key pressed
            char c = charFromEvent(event);
            msg_cmd[msg_cmd.length() - 1] = c;
            charPressed.setMessage(msg_cmd);

            // Update the shooter
            if(c == 'a')
                shooter.move(STEP_TIME, true);
            else if(c == 'd')
                shooter.move(STEP_TIME, false);
            else if(c == 'w')
                bullets.push_back(shooter.shoot());
            else if(c == 'q')
                return 0;
        }
          if (health==3){break;}//if health is finished stop the game
          if (seconds==515){break;}//if time is up stop the game
          int s=25-seconds/20.6,tenth_place,unit_place;//matching the frequency of the time in game with that in real world
          tenth_place=s/10;unit_place=s%10;
//            string msg_time("Time_Left:__");
//            Text Time_Remaining(LEFT_MARGIN, TOP_MARGIN, msg_time);
            msg_time[msg_time.length()-1] = 48+unit_place;msg_time[msg_time.length()-2] = 48+tenth_place;
            Time_Remaining.setMessage(msg_time);//print time with the help of ascii code values.

            msg_level[msg_level.length() - 1] = 49;
            Level_No.setMessage(msg_level);//print level with the help of ascii code values.

            msg_health[msg_health.length() - 3] = health + 48;
            Health_Reamaining.setMessage(msg_health);//print health with the help of ascii code values.

            msg_score[msg_score.length() - 2] = score + 48;
            Score.setMessage(msg_score);//print score with the help of ascii code values.

        // Update the bubbles
        move_bubbles(bubbles);

        // Update the bullets
        move_bullets(bullets);

        collision(bubbles,bullets,score,false_score);
        collision_with_shooter(bubbles,shooter,health,false_score);
        seconds+=1;
        wait(STEP_TIME);
    }}
    if (false_score>=4 && false_score< 12){
    vector<Bubble> bubbles = create_bubbles_level2();

    double seconds=0;

    while (false_score< 12)//check if minimum of 1 bubble from level 2 on screen
    {
        bool pendingEvent = checkEvent(event);
        if (pendingEvent)
        {
            // Get the key pressed
            char c = charFromEvent(event);
            msg_cmd[msg_cmd.length() - 1] = c;
            charPressed.setMessage(msg_cmd);



            // Update the shooter
            if(c == 'a')
                shooter.move(STEP_TIME, true);
            else if(c == 'd')
                shooter.move(STEP_TIME, false);
            else if(c == 'w')
                bullets.push_back(shooter.shoot());
            else if(c == 'q')
                return 0;
        }
            if(seconds==1071){break;}//if time is up stop the game

            if (health==3){break;}//if health is finished stop the game
            int s=50-seconds/21.42,tenth_place,unit_place;//matching the frequency of the time in game with real world
            tenth_place=s/10;unit_place=s%10;
//            string msg_time("Time_Left: "+to_string(s));
//            Text Time_Remaining(LEFT_MARGIN, TOP_MARGIN, msg_time);
             msg_time[msg_time.length()-1] = 48+unit_place;msg_time[msg_time.length()-2] = 48+tenth_place;
            Time_Remaining.setMessage(msg_time);//print time remaining using ascii values

            msg_level[msg_level.length() - 1] = 50;
            Level_No.setMessage(msg_level);//print level no using ascii values

            msg_health[msg_health.length() - 3] = health + 48;
            Health_Reamaining.setMessage(msg_health);//print health using ascii values

            msg_score[msg_score.length() - 2] = score + 48;
            Score.setMessage(msg_score);//print score using ascii values

        // Update the bubbles
        move_bubbles(bubbles);

        // Update the bullets
        move_bullets(bullets);

        collision(bubbles,bullets,score,false_score);
        collision_with_shooter(bubbles,shooter,health,false_score);
        seconds+=1;
        wait(STEP_TIME);
    }
}
// massages for win and loose situation
if(score==10 || score==11 || score==12){
string msg_win("CONGRATULATIONS!");
Text player_win(250,250,msg_win);
getClick();// Click to anywhere to exite the game
}
if(health==3 || true){
  if(health!=3){// checking the reason of loss
       string msg_loose_time("You ran out of Time");//lost because of time
       Text player_loose_time(250,250,msg_loose_time);
       getClick();// Click to anywhere to exite the game
        }
  else{
       string msg_loose_lives("You ran out of lives");//lost because of lives
       Text player_loose_lives(250,250,msg_loose_lives);
       getClick();// Click to anywhere to exite the game}
}
}}
