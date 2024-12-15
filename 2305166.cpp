#include "iGraphics.h"
#include<bits/stdc++.h>
using namespace std;
#define G 9.8
#define g 9.8/100 // will need this to manage timescale with gravity
#define PI 3.14159265
//sprites----------------------------------------------------------------------------------------------
Sprite bgmenu, PlayB , Logomain, logolalPakhi; 
Sprite sprite_enviro1[6],sprite_pillar[15], sprite_birds[4]; 
Sprite sprite_menu[13];
Image bg1, bg2;
Sprite enemy[3];
//-----------declaration of each sprite variable 
//methods----------------------------------------------------------------------------------------------
void change();
void pauser();
void loadResources();
int main();
void iDraw();
void BackandForth();
void calculate_score();
//variables-------------------------------------------------------------------------------------------
float x = 0, y = 0;
int red = 255, green = 255, blue = 255;
int x_offset=180, y_offset=120;
int theta = 0 ;//this keeps changing in the update function, according to where the mouse is
int yAxisD = 110 , xAxisD = 50, xArc =60 , yArc = 150, xCircle=x_offset+50, yCircle=y_offset+50, xLine= 120, yLine= 120+60 , radius = 50;
//ycircle from 70 to 160
int xBall = 70 , yBall = 160, radiusBall = 10;//yball 70 to 160 te
int check = 0, velocity = 15, timeChange = 0, timeMax = 100, R_max, velocity_x, velocity_y;
char birds[4][40]={"l1\\redP.png", "l1\\purpleP.png", "l1\\blueP.png","l1\\enemyP.png"};
char Menu[2][40]={"home\\How.png","home\\scorecard.png"};

//new string arrays 
char l1pill[15][40]={"l1\\pil1.png","l1\\pil2.png","l1\\pil3.png","l1\\pil4.png","l1\\pil5.png","l1\\pil6.png","l1\\pil7.png","l1\\pil8.png","l1\\pil9.png","l1\\pil10.png","l1\\pil11.png","l1\\pil12.png","l1\\pil13.png","l1\\pil14.png","l1\\pil15.png"};
char environment[6][40]={"l1\\level1BG.png","l1\\backdrop1.png","l1\\hillleft.png","l1\\hillright.png","l1\\rightbase.png","l1\\shooter.png"};
char MenuButton[13][40]={"home\\menubackground.png", "home\\PlayB.png" , "home\\HomeB.png", "home\\HowTo.png","home\\levelselector.png", "home\\settings.png", "home\\3birds.png", "home\\chillbirds.png", "extra\\playerchanger.png", "extra\\scoreshower.png","extra\\heart.png", "extra\\cloud.png", "extra\\cloud1.png"};//this is for the bg and menu

vector<int> pil_can_be_seen(15,1);
vector<int> collision_done_once(3,0);
int Bird_index = 0; 
vector<int> score_highs ;

bool show_projectile = 1;
int gameState = 0;
//level variables ----------------------------------------------------------------------------
int level1;
int Total_score = 0;
//--------------------------------------------------------------------------------------------

/* 
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/*
	function iPassiveMouseMove() is called automatically when the mouse pointer is in motion
*/
bool passive_mouse_valid = 1;
bool any_input_valid = 1;
void iPassiveMouseMove(int mx, int my)
{
	//place your code here
    if(gameState==1 && passive_mouse_valid==1 && any_input_valid==1){
    double x_component = mx-x_offset;
	double y_component = my-y_offset;

	int current_theta = atan2(y_component, x_component)*180/PI;
		if(current_theta>=10 && current_theta<=80){
        	theta = current_theta;
			
		}else if(current_theta<10){
			theta = 10;
		}else{
			theta = 80;
		}//theta maintaining update ----------------------------------------------------------->
		xLine = xCircle + (radius+50)*cos(theta*PI/180);
	    yLine = yCircle + (radius+50)*sin(theta*PI/180);

	}
}

/* 
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
bool gonna_launch = 0;
void iMouse(int button, int state, int mx, int my)
{

	if(gameState==0){
		//playbutton click detection 
		if(mx>=570 && mx<=830 && my>=175 && my<=250)
		{	
			//make the pillars seen
			show_projectile = 1;
			for(int i = 0; i < 15; i++){
			pil_can_be_seen[i]=1;
			}
			gameState=1; 
			loadResources();
		}
		//high score click detection
		if(mx>=35 && mx<=170 && my>=620 && my<=750)
		{
			calculate_score();
			gameState=-1;//highscore  
			loadResources();
		}
		//how to pageloader------------------->
		if(mx>=1320 && mx<=1455 && my>=20 && my<=155)
		{
			gameState=-2;//highscore  
			loadResources();
		}

	}else if(gameState==-1 || gameState==-2){
		if(mx>=1320 && mx<=1455 && my>=620 && my<=750)
		{
			gameState=0;//homeButton  
			loadResources();
		}
	}
	
	//need to fix the button clicks but launch stuff-----------------
	
    else if(gameState==1 && any_input_valid==1){
        if(mx>190){
		
		passive_mouse_valid = 0;
        //click launch update -_- 
        check = 1;
		timeMax= ((int)2*velocity*sin(theta*PI/180)/G)*100 + 2;
		R_max = (velocity*velocity*sin(2*theta)/2/G)*100;
		//cout << R_max;
		show_projectile = 0;
		cout << "the bird started"<<check << endl;
        iResumeTimer(level1);
        any_input_valid = 0;
		}
		else{
		show_projectile = 0;
		if(mx>=40 && mx<=175 && my>=320 && my<=450)
			{
				Bird_index++;
				Total_score-=5;                   //negative marking 
				loadResources();
				show_projectile = 1;
			}
		}
    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed. 
*/
void iKeyboard(unsigned char key)
{
    if(gameState==1){
		
	if (key == ' ' ) {
		
		check = 1;
		timeMax= ((int)2*velocity*sin(theta*PI/180)/G)*100 + 2;
		R_max = (velocity*velocity*sin(2*theta)/2/G)*100;
		//cout << R_max;
		show_projectile = 0;
		cout << "the bird started"<<check << endl;
        iResumeTimer(level1);
        any_input_valid = 0;
	}
	}
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use 
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, 
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, 
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT 
*/
void iSpecialKeyboard(unsigned char key)
{

	//keyboard projectile control done 
	if (key == GLUT_KEY_END) {
		exit(0);
	}
	if(gameState==1){
	if(key == GLUT_KEY_UP || key==GLUT_KEY_LEFT){
		if(theta <=80 && check == 0){
			theta+=5;	
			xLine = xCircle + (radius+50)*cos(theta*PI/180);
			yLine = yCircle + (radius+50)*sin(theta*PI/180);
		}
	}
	if(key == GLUT_KEY_DOWN || key==GLUT_KEY_RIGHT){
		if(theta >= 10 && check == 0){
			theta-=5;	
			xLine = xCircle + (radius+50)*cos(theta*PI/180);
			yLine = yCircle + (radius+50)*sin(theta*PI/180);
		}
	}
	}
}

int main()
{
	loadResources();
    //place your own initialization codes here.
	//we have to load all the timers here and then manually resume in the input
	level1 = iSetTimer(1,change);
	PlaySound("music\\m1.wav", NULL, SND_FILENAME | SND_ASYNC);
	//5 ta highscore data, eta ekta vector e nibo, then screen e dekhanor time e sort kore print.
	
	//this is loading the score list, now we have to open the high score page and print them in serial
	//and everytime a game ends

	pauser();
	iInitialize(1500,790, "ChillBirds"); 
	return 0;
}	

void pauser(){
	iPauseTimer(level1);//other levels are added to 
}

void change(){
	
	if(check){
		if(Bird_index%3==0){
			//redbird
			velocity = 15;
		}else if(Bird_index%3==1){
			//purple bird
			velocity = 20;
		}else{
			//blue bird
			velocity =10;//fluctuating the velocity has made the game difficult :(
		}
		sprite_birds[Bird_index%3].x = x_offset + velocity*cos(theta*PI / 180) *timeChange;
		sprite_birds[Bird_index%3].y = y_offset + (sprite_birds[Bird_index%3].x-x_offset)*tan(theta *PI / 180) - 0.5*g*(sprite_birds[Bird_index%3].x-x_offset)*(sprite_birds[Bird_index%3].x-x_offset) / (velocity*cos(theta*PI / 180)) / (velocity*cos(theta*PI / 180));//rmax diyeo kora jay
		if(timeChange!=timeMax+1000){
			timeChange+=2;//speed of animation(framerate)
			//cout << timeChange << " ";
		}
        //check collision----------------------------------------------------------------
        for(int i = 0; i < 15; i++){
            if(iCheckCollision(&sprite_pillar[i], &sprite_birds[Bird_index%3]) && pil_can_be_seen[i]==1){
                pil_can_be_seen[i] = 0;  
                cout << "collision ";
				//PlaySound("music\\col.wav", NULL, SND_FILENAME | SND_ASYNC);
                timeChange = 0; 
			    timeMax = 0;
			    check = 0;
			    sprite_birds[Bird_index%3].x = x_offset; sprite_birds[Bird_index%3].y = y_offset;//resetting problem appears when you have strict exact time, increment it by two 
			    show_projectile = 1;
			    theta = 10;
                passive_mouse_valid = 1; any_input_valid = 1;
			    iPauseTimer(level1);
				Total_score+=10;
				Bird_index++;//bird changes after every collision--------------
				loadResources();
            }
        }
		for(int i = 0; i < 3; i++){
			if(iCheckCollision(&enemy[i], &sprite_birds[Bird_index%3]) && collision_done_once[i]==0){
                timeChange = 0; 
			    timeMax = 0;
			    check = 0;
			    sprite_birds[Bird_index%3].x = x_offset; sprite_birds[Bird_index%3].y = y_offset;//resetting problem appears when you have strict exact time, increment it by two 
			    show_projectile = 1;
			    theta = 10;
                passive_mouse_valid = 1; any_input_valid = 1;
			    iPauseTimer(level1);
				Total_score-=10;
				collision_done_once[i]= 1;
				Bird_index++;//bird changes after every collision--------------
				loadResources();
            }
		}
        //--------------------------------------------------------------------------------
		if(sprite_birds[Bird_index%3].y<10 || sprite_birds[Bird_index%3].x >= 1500){
			timeChange = 0; 
			timeMax = 0;
			check = 0;
			sprite_birds[Bird_index%3].x = x_offset; sprite_birds[Bird_index%3].y = y_offset;//resetting problem appears when you have strict exact time, increment it by two 
			show_projectile = 1;
			theta = 10;
            passive_mouse_valid = 1; any_input_valid = 1;
			iPauseTimer(level1);
			if(Total_score>=20){Total_score-=20;}
			else Total_score = 0;                                    //negative markings
			Bird_index++;
			loadResources();
		}
		//level exit---------------------
		bool pillar_left = pil_can_be_seen[0]+pil_can_be_seen[1]+pil_can_be_seen[2]+pil_can_be_seen[3]+pil_can_be_seen[4]+pil_can_be_seen[5]+pil_can_be_seen[6]+pil_can_be_seen[7]+pil_can_be_seen[8]+pil_can_be_seen[9]+pil_can_be_seen[10]+pil_can_be_seen[11]+pil_can_be_seen[12]+pil_can_be_seen[13]+pil_can_be_seen[14];
		if(pillar_left==0){
			//ektao pillar nai 
			char score_var[4];
    		sprintf(score_var, "%d ", Total_score);
        	ofstream fout("data.txt", ios::app);
        	fout<<score_var;
        	fout.close();
			Total_score= 0;
			iPauseTimer(level1);
			gameState = 0;
			Bird_index = 0;
			//loadResources();
		}
	}
}
void loadResources()
{
    
    if(gameState == 0){
		
        iLoadSprite(&sprite_menu[0],MenuButton[0], -1);
        iSetSpritePosition(&sprite_menu[0], 0, 0);//menu background loader 

        iLoadSprite(&sprite_menu[1], MenuButton[1], 0xFFFFFF);
        iSetSpritePosition(&sprite_menu[1],550,150);            //playbutton
		iLoadSprite(&sprite_menu[3], MenuButton[3], 0xFFFFFF);
        iSetSpritePosition(&sprite_menu[3],1300,20);            //HowTobutton
		iLoadSprite(&sprite_menu[4], MenuButton[4], 0xFFFFFF);
        iSetSpritePosition(&sprite_menu[4],20,600);            //Highscore table
		iLoadSprite(&sprite_menu[5], MenuButton[5], 0xFFFFFF);
        iSetSpritePosition(&sprite_menu[5],1300,600);            //settings

		iLoadSprite(&sprite_menu[6], MenuButton[6], 0xFFFFFF);
        iSetSpritePosition(&sprite_menu[6],530,400);            //parindas
		double parindaAspectRatio = (double)sprite_menu[6].img.width / sprite_menu[6].img.height;
        iResizeSprite(&sprite_menu[6], 480, 480.0 / parindaAspectRatio);
		
		iLoadSprite(&sprite_menu[7], MenuButton[7], 0xFFFFFF);
        iSetSpritePosition(&sprite_menu[7],370,220);            //logochillbids
		double chillbirdsAspectRatio = (double)sprite_menu[7].img.width / sprite_menu[7].img.height;
        iResizeSprite(&sprite_menu[7], 700, 700.0 / chillbirdsAspectRatio);

    }else if(gameState==1){
        //level 1--------------------------------------------------------------------------------------------------------------
		//make the pillars seen 
		
        //scenery settings
        iLoadSprite(&sprite_enviro1[0],environment[0],-1);
        iSetSpritePosition(&sprite_enviro1[0],0,0);                          //background 
		double bgAspectRatio = (double)sprite_enviro1[0].img.width / sprite_enviro1[0].img.height;
    	iResizeSprite(&sprite_enviro1[0], 1550, 1550.0 / bgAspectRatio);

        iLoadSprite(&sprite_enviro1[1],environment[1],0xFFFFFF);
		iSetSpritePosition(&sprite_enviro1[1],0,0);                          //blue mountains
        iLoadSprite(&sprite_enviro1[2], environment[2], 0xFFFFFF);
        iSetSpritePosition(&sprite_enviro1[2], 0 , 0);                       //lefthill
        iLoadSprite(&sprite_enviro1[3], environment[3], 0xFFFFFF);
        iSetSpritePosition(&sprite_enviro1[3], 860, 0);                       //righthill
        iLoadSprite(&sprite_enviro1[4], environment[4], 0xFFFFFF);
        iSetSpritePosition(&sprite_enviro1[4], 882, 0);                       //rightbase
        iLoadSprite(&sprite_enviro1[5], environment[5], 0xFFFFFF);
        iSetSpritePosition(&sprite_enviro1[5], 200, 40);                       //shooter
        //pillar settings
        if(pil_can_be_seen[0]){iLoadSprite(&sprite_pillar[0], l1pill[0], 0xFFFFFF);//pill1
        iSetSpritePosition(&sprite_pillar[0], 980, 185);                       }
        if(pil_can_be_seen[1]){iLoadSprite(&sprite_pillar[1], l1pill[1], 0xFFFFFF);//pill2
        iSetSpritePosition(&sprite_pillar[1], 1000, 45);                       }
        if(pil_can_be_seen[2]){iLoadSprite(&sprite_pillar[2], l1pill[2], 0xFFFFFF);//pill3
        iSetSpritePosition(&sprite_pillar[2], 1025, 45);                       }
		if(pil_can_be_seen[3]){
			iLoadSprite(&sprite_pillar[3], l1pill[3], 0xFFFFFF);//pill4
        	iSetSpritePosition(&sprite_pillar[3], 1125, 45); 
			iLoadSprite(&enemy[2], birds[3], 0xFFFFFF);
        	iSetSpritePosition(&enemy[2],1050,65);        //enemies    
			collision_done_once[2] = 1;                  
		}
		if(pil_can_be_seen[4]){iLoadSprite(&sprite_pillar[4], l1pill[4], 0xFFFFFF);//pill5
        iSetSpritePosition(&sprite_pillar[4], 1100, 260);                       }
		if(pil_can_be_seen[5]){
			iLoadSprite(&sprite_pillar[5], l1pill[5], 0xFFFFFF);//pill6
        	iSetSpritePosition(&sprite_pillar[5], 1175, 208);                       
			iLoadSprite(&enemy[0], birds[3], 0xFFFFFF);
        	iSetSpritePosition(&enemy[0],1200, 200);        //enemies
			collision_done_once[0] = 1;
		}
		if(pil_can_be_seen[6]){
			iLoadSprite(&sprite_pillar[6], l1pill[6], 0xFFFFFF);//pill7
        	iSetSpritePosition(&sprite_pillar[6], 1165, 175);
		}
		if(pil_can_be_seen[7]){iLoadSprite(&sprite_pillar[7], l1pill[7], 0xFFFFFF);//pill8
        iSetSpritePosition(&sprite_pillar[7], 1185, 45);                       }
		if(pil_can_be_seen[8]){iLoadSprite(&sprite_pillar[8], l1pill[8], 0xFFFFFF);//pill9
        iSetSpritePosition(&sprite_pillar[8], 1240, 40);                       }
		if(pil_can_be_seen[9]){iLoadSprite(&sprite_pillar[9], l1pill[9], 0xFFFFFF);//pill10
        iSetSpritePosition(&sprite_pillar[9], 1270, 45);                       }
		if(pil_can_be_seen[10]){iLoadSprite(&sprite_pillar[10], l1pill[10], 0xFFFFFF);//pill11
        iSetSpritePosition(&sprite_pillar[10], 1350, 45);                       }
		if(pil_can_be_seen[11]){iLoadSprite(&sprite_pillar[11], l1pill[11], 0xFFFFFF);//pill12
        iSetSpritePosition(&sprite_pillar[11], 1310, 108);                       }
		if(pil_can_be_seen[12]){iLoadSprite(&sprite_pillar[12], l1pill[12], 0xFFFFFF);//pill13
        iSetSpritePosition(&sprite_pillar[12], 1270, 305);                       }
		if(pil_can_be_seen[13]){
			iLoadSprite(&sprite_pillar[13], l1pill[13], 0xFFFFFF);//pill14
        	iSetSpritePosition(&sprite_pillar[13], 1240, 360);                       
			//ekhane arekta enemy 
			iLoadSprite(&enemy[1], birds[3], 0xFFFFFF);
        	iSetSpritePosition(&enemy[1],1240, 400);        //enemies
			collision_done_once[1] = 1;
		}
		if(pil_can_be_seen[14]){iLoadSprite(&sprite_pillar[14], l1pill[14], 0xFFFFFF);//pill15
        iSetSpritePosition(&sprite_pillar[14], 1120, 270);                       }

        //birds
        iLoadSprite(&sprite_birds[Bird_index%3], birds[Bird_index%3], 0xFFFFFF);
        iSetSpritePosition(&sprite_birds[Bird_index%3],x_offset,y_offset);//need to fix the coordinates bro
        //age 3 pillar niye dekh j kaaje dey kina--------------------------------------------
        //check by loops with whom it collides 
		iLoadSprite(&sprite_menu[2], MenuButton[2], 0xFFFFFF);
        iSetSpritePosition(&sprite_menu[2],1300,600);            //HOMEb
		iLoadSprite(&sprite_menu[8], MenuButton[8], 0xFFFFFF);
        iSetSpritePosition(&sprite_menu[8],20,300);            //playerchanger 
		//enemies
		iLoadSprite(&sprite_menu[9], MenuButton[9], 0x000000);
        iSetSpritePosition(&sprite_menu[9],10,600);            //wings
		

    }else if(gameState==-1){
		//show the home menu 
		iLoadSprite(&sprite_menu[2], MenuButton[2], 0xFFFFFF);
        iSetSpritePosition(&sprite_menu[2],1300,600);             //HOMEb
		iLoadImage(&bg1, Menu[1]);
	}else if(gameState == -2){
		//show the home menu 
		iLoadSprite(&sprite_menu[2], MenuButton[2], 0xFFFFFF);
        iSetSpritePosition(&sprite_menu[2],1300,600);             //HOMEb
		iLoadImage(&bg2, Menu[0]);
	}
    
}
void iDraw()
{
    /*
    if (iCheckCollision(&mario1, &mario2)) {
        iText(100, 500, "Collision Detected", GLUT_BITMAP_TIMES_ROMAN_24);
    }
    iShowSprite(&rect);
    if (iCheckCollision(&mario1, &rect)) {
        iText(100, 500, "Collision Detected", GLUT_BITMAP_TIMES_ROMAN_24);
    }*/
    
    if(gameState == 0){
		//home page------------------------------------------------------------------------------------------------------------
		iClear();
        iShowSprite(&sprite_menu[0]);
        iShowSprite(&sprite_menu[3]);
		iShowSprite(&sprite_menu[4]);
		iShowSprite(&sprite_menu[5]);
		iShowSprite(&sprite_menu[6]);
		iShowSprite(&sprite_menu[7]);
        iShowSprite(&sprite_menu[1]);


		/*
		iSetColor(255, 0, 0);
		iLine(35, 620 , 170, 620); //xanchor
		iLine(35, 620, 35, 750); //yanchor
		*/
        
	}
	else if(gameState==1){
		//level 1--------------------------------------------------------------------------------------------------------------
		iClear();//everything under this
		iShowSprite(&sprite_enviro1[0]);
        iShowSprite(&sprite_enviro1[1]);
        iShowSprite(&sprite_enviro1[2]);
        iShowSprite(&sprite_enviro1[3]);
        iShowSprite(&sprite_enviro1[4]);
        iShowSprite(&sprite_enviro1[5]);
		iShowSprite(&sprite_menu[8]);//this is for the big globe 
		iShowSprite(&sprite_menu[9]);//wings

		//pillars 
        for(int i = 0; i< 15; i++){
			if(pil_can_be_seen[i])iShowSprite(&sprite_pillar[i]);
		}
		iSetColor(255, 0, 0);
		//iLine(50, yAxisD, 900, yAxisD); //xAxis
		//iLine(xAxisD, 50, xAxisD, 600); //yAxis
		iSetColor(255, 255, 255); /// xaxisdraw to xaxisd
		//iCircle(xCircle - 10, yCircle - 7, radius, 100); // xcircle to xarc 
		if(show_projectile){
			iSetColor(255, 255, 255);
			//iLine (xCircle, yCircle, xLine, yLine);//projectile line 
			//selective showing of things implemented
			//this is where we write the curve equation
			if(Bird_index%3==0){
				//redbird
				velocity = 15;
			}else if(Bird_index%3==1){
				//purple bird
				velocity = 20;
			}else{
				//blue bird
				velocity =10;//fluctuating the velocity has made the game difficult :(
			}
			//theta ache
			R_max = (velocity*velocity*sin(2*theta)/2/G)*100;
			for(int i = 0; i < 1400;i+=30){
				//xLine er change thik ache, just yline change korte hobe
				int x_now = x_offset+100 + i;
				int y_now = y_offset+50 + (x_now-x_offset)*tan(theta *PI / 180) - 0.5*g*(x_now-x_offset)*(x_now-x_offset) / (velocity*cos(theta*PI / 180)) / (velocity*cos(theta*PI / 180));//rmax diyeo kora jay
				iFilledCircle(x_now , y_now, 5, 100);
			}
			
		}
		iSetColor(0, 255, 0);
		//iFilledCircle(xBall, yBall, radiusBall*2, 1000); 
		//iShowBMP2(xBall-50,yBall-50,birds[Bird_index],0);//show birds
        iShowSprite(&sprite_birds[Bird_index%3]);

		if(pil_can_be_seen[5])iShowSprite(&enemy[0]);             //enemy 
		if(pil_can_be_seen[13])iShowSprite(&enemy[1]);
		if(pil_can_be_seen[3])iShowSprite(&enemy[2]);

		//score showing 
		iSetColor(0, 0, 0);
		char scoreshow[50];
    	sprintf(scoreshow, "Score: %d", Total_score);
		iText(220, 690, scoreshow , GLUT_BITMAP_HELVETICA_18);        //score update

	}
	else if(gameState == -1){
		//score showing 
		iClear();
		//logic---------------------------------------------------------------------------------
		
		iShowImage(0,0,&bg1);//background	
		iShowSprite(&sprite_menu[2]);
		
		//score update
		int p = score_highs.size();
		if(p>5)p=5;
		int dist = 100;
		iSetColor(0, 0, 0);
		char scoreshow[50];
    	
		for(int i = 0; i<p;i++){
			sprintf(scoreshow, " %d", score_highs[i]);
			iText(750, 650-dist, scoreshow , GLUT_BITMAP_HELVETICA_18); 
			dist+=70;
		}
		iShowSprite(&sprite_menu[2]);
		//after score_high clear the vector v---------------------------

	}else if(gameState==-2){
		iClear();
		iShowImage(0,0,&bg2);//background	
		iShowSprite(&sprite_menu[2]);
	}
}
void calculate_score(){
	string filename = "data.txt";
        char score_list[10000];
        ifstream fin(filename);
		fin.getline(score_list, 10000);//read everything in this array
        fin.close();
        int curr_num = 0;
        for(int i = 0 ; score_list[i]!=EOF ; i++)
        {
            if(score_list[i]!=' '&&  score_list[i]>='0' && score_list[i]<='9'){
                curr_num = curr_num*10 + (int)(score_list[i]-'0');
            }else if(score_list[i]==' '){
                score_highs.push_back(curr_num);
                curr_num = 0;
            }else{
                continue;
            }
        }
        sort(score_highs.rbegin(), score_highs.rend());//sorting process o done 
		//ekhan theke first 5 ta print korbo -_- 
		//drawing-------------------------------------------------------------------------------
		int index = unique(score_highs.begin(), score_highs.end()) - score_highs.begin();
        score_highs.resize(index);
}