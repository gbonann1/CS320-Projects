#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

unsigned long long addr;
char behavior[10];

//for bimodal 1 bit
int correct16 = 0;
int correct32 = 0;
int correct128 = 0;
int correct256 = 0;
int correct512 = 0;
int correct1024 = 0;
int correct2048 = 0;
int predictor16[16];
int predictor32[32];
int predictor128[128];
int predictor256[256];
int predictor512[512];
int predictor1024[1024];
int predictor2048[2048];

typedef struct Predictor{
	int strong;
	int taken;
	
}Predictor;


Predictor * makePredictor(){
	Predictor *newPredictor;
	newPredictor = (Predictor*)malloc(sizeof(Predictor));
	newPredictor->strong = 1;
	newPredictor->taken = 1;
	return newPredictor;
}

//for bimodal 2 bit
int bcorrect16 = 0;
int bcorrect32 = 0;
int bcorrect128 = 0;
int bcorrect256 = 0;
int bcorrect512 = 0;
int bcorrect1024 = 0;
int bcorrect2048 = 0;
Predictor bpredictor16[16];
Predictor bpredictor32[32];
Predictor bpredictor128[128];
Predictor bpredictor256[256];
Predictor bpredictor512[512];
Predictor bpredictor1024[1024];
Predictor bpredictor2048[2048];

//for gshare
int gshare3bit = 0;
int gshare4bit = 0;
int gshare5bit = 0;
int gshare6bit = 0;
int gshare7bit = 0;
int gshare8bit = 0;
int gshare9bit = 0;
int gshare10bit = 0;
int gshare11bit = 0;
int history3 = 0;
int history4 = 0;
int history5 = 0;
int history6 = 0;
int history7 = 0;
int history8 = 0;
int history9 = 0;
int history10 = 0;
int history11= 0;
Predictor gsharePredictor3[2048];
Predictor gsharePredictor4[2048];
Predictor gsharePredictor5[2048];
Predictor gsharePredictor6[2048];
Predictor gsharePredictor7[2048];
Predictor gsharePredictor8[2048];
Predictor gsharePredictor9[2048];
Predictor gsharePredictor10[2048];
Predictor gsharePredictor11[2048];

//tournament
int tournamentCount = 0;
int selector[2048];
Predictor gshareP[2048];
Predictor bimodalP[2048];
int gshareTrue = 0;
int bimodalTrue = 0;
int history12 = 0;

void bimodal1(){
	
	char taken;
	if (predictor16[addr%16] == 1 && !strncmp(behavior, "T", 2)) {
		correct16++;
	}	
	else if(predictor16[addr%16] == 0 && !strncmp(behavior, "NT", 2)) {
		correct16++;
	}
	if(!strncmp(behavior, "T", 2))
		predictor16[addr%16] = 1;
	else
		predictor16[addr%16] = 0;

	if (predictor32[addr%32] == 1 && !strncmp(behavior, "T", 2)) {
		correct32++;
	}	
	else if(predictor32[addr%32] == 0 && !strncmp(behavior, "NT", 2)) {
		correct32++;
	}
	if(!strncmp(behavior, "T", 2))
		predictor32[addr%32] = 1;
	else
		predictor32[addr%32] = 0;

	if (predictor128[addr%128] == 1 && !strncmp(behavior, "T", 2)) {
		correct128++;
	}	
	else if(predictor128[addr%128] == 0 && !strncmp(behavior, "NT", 2)) {
		correct128++;
	}
	if(!strncmp(behavior, "T", 2))
		predictor128[addr%128] = 1;
	else
		predictor128[addr%128] = 0;

	if (predictor256[addr%256] == 1 && !strncmp(behavior, "T", 2)) {
		correct256++;
	}	
	else if(predictor256[addr%256] == 0 && !strncmp(behavior, "NT", 2)) {
		correct256++;
	}
	if(!strncmp(behavior, "T", 2))
		predictor256[addr%256] = 1;
	else
		predictor256[addr%256] = 0;

	if (predictor512[addr%512] == 1 && !strncmp(behavior, "T", 2)) {
		correct512++;
	}	
	else if(predictor512[addr%512] == 0 && !strncmp(behavior, "NT", 2)) {
		correct512++;
	}
	if(!strncmp(behavior, "T", 2))
		predictor512[addr%512] = 1;
	else
		predictor512[addr%512] = 0;

	if (predictor1024[addr%1024] == 1 && !strncmp(behavior, "T", 2)) {
		correct1024++;
	}	
	else if(predictor1024[addr%1024] == 0 && !strncmp(behavior, "NT", 2)) {
		correct1024++;
	}
	if(!strncmp(behavior, "T", 2))
		predictor1024[addr%1024] = 1;
	else
		predictor1024[addr%1024] = 0;	

	if (predictor2048[addr%2048] == 1 && !strncmp(behavior, "T", 2)) {
		correct2048++;
	}	
	else if(predictor2048[addr%2048] == 0 && !strncmp(behavior, "NT", 2)) {
		correct2048++;
	}
	if(!strncmp(behavior, "T", 2))
		predictor2048[addr%2048] = 1;
	else
		predictor2048[addr%2048] = 0;
}

void bimodal2(){

	if (bpredictor16[addr%16].taken == 1 && !strncmp(behavior, "T", 2)) {
		bcorrect16++;
	}	
	else if(bpredictor16[addr%16].taken == 0 && !strncmp(behavior, "NT", 2)) {
		bcorrect16++;
	}
	if(!strncmp(behavior, "T", 2) && bpredictor16[addr%16].taken == 1 && bpredictor16[addr%16].strong == 0)
		bpredictor16[addr%16].strong = 1;
	else if(!strncmp(behavior, "T", 2) && bpredictor16[addr%16].taken == 0 && bpredictor16[addr%16].strong == 1)
		bpredictor16[addr%16].strong = 0;
	else if(!strncmp(behavior, "T", 2) && bpredictor16[addr%16].taken == 0 && bpredictor16[addr%16].strong == 0)
		bpredictor16[addr%16].taken = 1;
	else if(!strncmp(behavior, "NT", 2) && bpredictor16[addr%16].taken == 0 && bpredictor16[addr%16].strong == 0)
		bpredictor16[addr%16].strong = 1;
	else if(!strncmp(behavior, "NT", 2) && bpredictor16[addr%16].taken == 1 && bpredictor16[addr%16].strong == 1)
		bpredictor16[addr%16].strong = 0;
	else if(!strncmp(behavior, "NT", 2) && bpredictor16[addr%16].taken == 1 && bpredictor16[addr%16].strong == 0)
		bpredictor16[addr%16].taken = 0;

	if (bpredictor32[addr%32].taken == 1 && !strncmp(behavior, "T", 2)) {
		bcorrect32++;
	}	
	else if(bpredictor32[addr%32].taken == 0 && !strncmp(behavior, "NT", 2)) {
		bcorrect32++;
	}
	if(!strncmp(behavior, "T", 2) && bpredictor32[addr%32].taken == 1 && bpredictor32[addr%32].strong == 0)
		bpredictor32[addr%32].strong = 1;
	else if(!strncmp(behavior, "T", 2) && bpredictor32[addr%32].taken == 0 && bpredictor32[addr%32].strong == 1)
		bpredictor32[addr%32].strong = 0;
	else if(!strncmp(behavior, "T", 2) && bpredictor32[addr%32].taken == 0 && bpredictor32[addr%32].strong == 0)
		bpredictor32[addr%32].taken = 1;
	else if(!strncmp(behavior, "NT", 2) && bpredictor32[addr%32].taken == 0 && bpredictor32[addr%32].strong == 0)
		bpredictor32[addr%32].strong = 1;
	else if(!strncmp(behavior, "NT", 2) && bpredictor32[addr%32].taken == 1 && bpredictor32[addr%32].strong == 1)
		bpredictor32[addr%32].strong = 0;
	else if(!strncmp(behavior, "NT", 2) && bpredictor32[addr%32].taken == 1 && bpredictor32[addr%32].strong == 0)
		bpredictor32[addr%32].taken = 0;

	if (bpredictor128[addr%128].taken == 1 && !strncmp(behavior, "T", 2)) {
		bcorrect128++;
	}	
	else if(bpredictor128[addr%128].taken == 0 && !strncmp(behavior, "NT", 2)) {
		bcorrect128++;
	}
	if(!strncmp(behavior, "T", 2) && bpredictor128[addr%128].taken == 1 && bpredictor128[addr%128].strong == 0)
		bpredictor128[addr%128].strong = 1;
	else if(!strncmp(behavior, "T", 2) && bpredictor128[addr%128].taken == 0 && bpredictor128[addr%128].strong == 1)
		bpredictor128[addr%128].strong = 0;
	else if(!strncmp(behavior, "T", 2) && bpredictor128[addr%128].taken == 0 && bpredictor128[addr%128].strong == 0)
		bpredictor128[addr%128].taken = 1;
	else if(!strncmp(behavior, "NT", 2) && bpredictor128[addr%128].taken == 0 && bpredictor128[addr%128].strong == 0)
		bpredictor128[addr%128].strong = 1;
	else if(!strncmp(behavior, "NT", 2) && bpredictor128[addr%128].taken == 1 && bpredictor128[addr%128].strong == 1)
		bpredictor128[addr%128].strong = 0;
	else if(!strncmp(behavior, "NT", 2) && bpredictor128[addr%128].taken == 1 && bpredictor128[addr%128].strong == 0)
		bpredictor128[addr%128].taken = 0;

	if (bpredictor256[addr%256].taken == 1 && !strncmp(behavior, "T", 2)) {
		bcorrect256++;
	}	
	else if(bpredictor256[addr%256].taken == 0 && !strncmp(behavior, "NT", 2)) {
		bcorrect256++;
	}
	if(!strncmp(behavior, "T", 2) && bpredictor256[addr%256].taken == 1 && bpredictor256[addr%256].strong == 0)
		bpredictor256[addr%256].strong = 1;
	else if(!strncmp(behavior, "T", 2) && bpredictor256[addr%256].taken == 0 && bpredictor256[addr%256].strong == 1)
		bpredictor256[addr%256].strong = 0;
	else if(!strncmp(behavior, "T", 2) && bpredictor256[addr%256].taken == 0 && bpredictor256[addr%256].strong == 0)
		bpredictor256[addr%256].taken = 1;
	else if(!strncmp(behavior, "NT", 2) && bpredictor256[addr%256].taken == 0 && bpredictor256[addr%256].strong == 0)
		bpredictor256[addr%256].strong = 1;
	else if(!strncmp(behavior, "NT", 2) && bpredictor256[addr%256].taken == 1 && bpredictor256[addr%256].strong == 1)
		bpredictor256[addr%256].strong = 0;
	else if(!strncmp(behavior, "NT", 2) && bpredictor256[addr%256].taken == 1 && bpredictor256[addr%256].strong == 0)
		bpredictor256[addr%256].taken = 0;

	if (bpredictor512[addr%512].taken == 1 && !strncmp(behavior, "T", 2)) {
		bcorrect512++;
	}	
	else if(bpredictor512[addr%512].taken == 0 && !strncmp(behavior, "NT", 2)) {
		bcorrect512++;
	}
	if(!strncmp(behavior, "T", 2) && bpredictor512[addr%512].taken == 1 && bpredictor512[addr%512].strong == 0)
		bpredictor512[addr%512].strong = 1;
	else if(!strncmp(behavior, "T", 2) && bpredictor512[addr%512].taken == 0 && bpredictor512[addr%512].strong == 1)
		bpredictor512[addr%512].strong = 0;
	else if(!strncmp(behavior, "T", 2) && bpredictor512[addr%512].taken == 0 && bpredictor512[addr%512].strong == 0)
		bpredictor512[addr%512].taken = 1;
	else if(!strncmp(behavior, "NT", 2) && bpredictor512[addr%512].taken == 0 && bpredictor512[addr%512].strong == 0)
		bpredictor512[addr%512].strong = 1;
	else if(!strncmp(behavior, "NT", 2) && bpredictor512[addr%512].taken == 1 && bpredictor512[addr%512].strong == 1)
		bpredictor512[addr%512].strong = 0;
	else if(!strncmp(behavior, "NT", 2) && bpredictor512[addr%512].taken == 1 && bpredictor512[addr%512].strong == 0)
		bpredictor512[addr%512].taken = 0;

	if (bpredictor1024[addr%1024].taken == 1 && !strncmp(behavior, "T", 2)) {
		bcorrect1024++;
	}	
	else if(bpredictor1024[addr%1024].taken == 0 && !strncmp(behavior, "NT", 2)) {
		bcorrect1024++;
	}
	if(!strncmp(behavior, "T", 2) && bpredictor1024[addr%1024].taken == 1 && bpredictor1024[addr%1024].strong == 0)
		bpredictor1024[addr%1024].strong = 1;
	else if(!strncmp(behavior, "T", 2) && bpredictor1024[addr%1024].taken == 0 && bpredictor1024[addr%1024].strong == 1)
		bpredictor1024[addr%1024].strong = 0;
	else if(!strncmp(behavior, "T", 2) && bpredictor1024[addr%1024].taken == 0 && bpredictor1024[addr%1024].strong == 0)
		bpredictor1024[addr%1024].taken = 1;
	else if(!strncmp(behavior, "NT", 2) && bpredictor1024[addr%1024].taken == 0 && bpredictor1024[addr%1024].strong == 0)
		bpredictor1024[addr%1024].strong = 1;
	else if(!strncmp(behavior, "NT", 2) && bpredictor1024[addr%1024].taken == 1 && bpredictor1024[addr%1024].strong == 1)
		bpredictor1024[addr%1024].strong = 0;
	else if(!strncmp(behavior, "NT", 2) && bpredictor1024[addr%1024].taken == 1 && bpredictor1024[addr%1024].strong == 0)
		bpredictor1024[addr%1024].taken = 0;

	if (bpredictor2048[addr%2048].taken == 1 && !strncmp(behavior, "T", 2)) {
		bcorrect2048++;
	}	
	else if(bpredictor2048[addr%2048].taken == 0 && !strncmp(behavior, "NT", 2)) {
		bcorrect2048++;
	}
	if(!strncmp(behavior, "T", 2) && bpredictor2048[addr%2048].taken == 1 && bpredictor2048[addr%2048].strong == 0)
		bpredictor2048[addr%2048].strong = 1;
	else if(!strncmp(behavior, "T", 2) && bpredictor2048[addr%2048].taken == 0 && bpredictor2048[addr%2048].strong == 1)
		bpredictor2048[addr%2048].strong = 0;
	else if(!strncmp(behavior, "T", 2) && bpredictor2048[addr%2048].taken == 0 && bpredictor2048[addr%2048].strong == 0)
		bpredictor2048[addr%2048].taken = 1;
	else if(!strncmp(behavior, "NT", 2) && bpredictor2048[addr%2048].taken == 0 && bpredictor2048[addr%2048].strong == 0)
		bpredictor2048[addr%2048].strong = 1;
	else if(!strncmp(behavior, "NT", 2) && bpredictor2048[addr%2048].taken == 1 && bpredictor2048[addr%2048].strong == 1)
		bpredictor2048[addr%2048].strong = 0;
	else if(!strncmp(behavior, "NT", 2) && bpredictor2048[addr%2048].taken == 1 && bpredictor2048[addr%2048].strong == 0)
		bpredictor2048[addr%2048].taken = 0;
		

}

void gshare(){

	if (gsharePredictor3[addr%2048^history3%2048].taken == 1 && !strncmp(behavior, "T", 2)) {
		gshare3bit++;
	}	
	else if(gsharePredictor3[addr%2048^history3%2048].taken == 0 && !strncmp(behavior, "NT", 2)) {
		gshare3bit++;
	}
	if(!strncmp(behavior, "T", 2) && gsharePredictor3[addr%2048^history3%2048].taken == 1 && gsharePredictor3[addr%2048^history3%2048].strong == 0)
		gsharePredictor3[addr%2048^history3%2048].strong = 1;
	else if(!strncmp(behavior, "T", 2) && gsharePredictor3[addr%2048^history3%2048].taken == 0 && gsharePredictor3[addr%2048^history3%2048].strong == 1)
		gsharePredictor3[addr%2048^history3%2048].strong = 0;
	else if(!strncmp(behavior, "T", 2) && gsharePredictor3[addr%2048^history3%2048].taken == 0 && gsharePredictor3[addr%2048^history3%2048].strong == 0)
		gsharePredictor3[addr%2048^history3%2048].taken = 1;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor3[addr%2048^history3%2048].taken == 0 && gsharePredictor3[addr%2048^history3%2048].strong == 0)
		gsharePredictor3[addr%2048^history3%2048].strong = 1;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor3[addr%2048^history3%2048].taken == 1 && gsharePredictor3[addr%2048^history3%2048].strong == 1)
		gsharePredictor3[addr%2048^history3%2048].strong = 0;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor3[addr%2048^history3%2048].taken == 1 && gsharePredictor3[addr%2048^history3%2048].strong == 0)
		gsharePredictor3[addr%2048^history3%2048].taken = 0;

	history3 = history3 << 1;
	history3 = history3 & 7;
	if (!strncmp(behavior, "T", 2))
		history3 = history3 | 1;

	if (gsharePredictor4[addr%2048^history4%2048].taken == 1 && !strncmp(behavior, "T", 2)) {
		gshare4bit++;
	}	
	else if(gsharePredictor4[addr%2048^history4%2048].taken == 0 && !strncmp(behavior, "NT", 2)) {
		gshare4bit++;
	}
	if(!strncmp(behavior, "T", 2) && gsharePredictor4[addr%2048^history4%2048].taken == 1 && gsharePredictor4[addr%2048^history4%2048].strong == 0)
		gsharePredictor4[addr%2048^history4%2048].strong = 1;
	else if(!strncmp(behavior, "T", 2) && gsharePredictor4[addr%2048^history4%2048].taken == 0 && gsharePredictor4[addr%2048^history4%2048].strong == 1)
		gsharePredictor4[addr%2048^history4%2048].strong = 0;
	else if(!strncmp(behavior, "T", 2) && gsharePredictor4[addr%2048^history4%2048].taken == 0 && gsharePredictor4[addr%2048^history4%2048].strong == 0)
		gsharePredictor4[addr%2048^history4%2048].taken = 1;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor4[addr%2048^history4%2048].taken == 0 && gsharePredictor4[addr%2048^history4%2048].strong == 0)
		gsharePredictor4[addr%2048^history4%2048].strong = 1;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor4[addr%2048^history4%2048].taken == 1 && gsharePredictor4[addr%2048^history4%2048].strong == 1)
		gsharePredictor4[addr%2048^history4%2048].strong = 0;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor4[addr%2048^history4%2048].taken == 1 && gsharePredictor4[addr%2048^history4%2048].strong == 0)
		gsharePredictor4[addr%2048^history4%2048].taken = 0;

	history4 = history4 << 1;
	history4 = history4 & 15;
	if (!strncmp(behavior, "T", 2))
		history4 = history4 | 1;

	if (gsharePredictor5[addr%2048^history5%2048].taken == 1 && !strncmp(behavior, "T", 2)) {
		gshare5bit++;
	}	
	else if(gsharePredictor5[addr%2048^history5%2048].taken == 0 && !strncmp(behavior, "NT", 2)) {
		gshare5bit++;
	}
	if(!strncmp(behavior, "T", 2) && gsharePredictor5[addr%2048^history5%2048].taken == 1 && gsharePredictor5[addr%2048^history5%2048].strong == 0)
		gsharePredictor5[addr%2048^history5%2048].strong = 1;
	else if(!strncmp(behavior, "T", 2) && gsharePredictor5[addr%2048^history5%2048].taken == 0 && gsharePredictor5[addr%2048^history5%2048].strong == 1)
		gsharePredictor5[addr%2048^history5%2048].strong = 0;
	else if(!strncmp(behavior, "T", 2) && gsharePredictor5[addr%2048^history5%2048].taken == 0 && gsharePredictor5[addr%2048^history5%2048].strong == 0)
		gsharePredictor5[addr%2048^history5%2048].taken = 1;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor5[addr%2048^history5%2048].taken == 0 && gsharePredictor5[addr%2048^history5%2048].strong == 0)
		gsharePredictor5[addr%2048^history5%2048].strong = 1;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor5[addr%2048^history5%2048].taken == 1 && gsharePredictor5[addr%2048^history5%2048].strong == 1)
		gsharePredictor5[addr%2048^history5%2048].strong = 0;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor5[addr%2048^history5%2048].taken == 1 && gsharePredictor5[addr%2048^history5%2048].strong == 0)
		gsharePredictor5[addr%2048^history5%2048].taken = 0;

	history5 = history5 << 1;
	history5 = history5 & 31;
	if (!strncmp(behavior, "T", 2))
		history5 = history5 | 1;

	if (gsharePredictor6[addr%2048^history6%2048].taken == 1 && !strncmp(behavior, "T", 2)) {
		gshare6bit++;
	}	
	else if(gsharePredictor6[addr%2048^history6%2048].taken == 0 && !strncmp(behavior, "NT", 2)) {
		gshare6bit++;
	}
	if(!strncmp(behavior, "T", 2) && gsharePredictor6[addr%2048^history6%2048].taken == 1 && gsharePredictor6[addr%2048^history6%2048].strong == 0)
		gsharePredictor6[addr%2048^history6%2048].strong = 1;
	else if(!strncmp(behavior, "T", 2) && gsharePredictor6[addr%2048^history6%2048].taken == 0 && gsharePredictor6[addr%2048^history6%2048].strong == 1)
		gsharePredictor6[addr%2048^history6%2048].strong = 0;
	else if(!strncmp(behavior, "T", 2) && gsharePredictor6[addr%2048^history6%2048].taken == 0 && gsharePredictor6[addr%2048^history6%2048].strong == 0)
		gsharePredictor6[addr%2048^history6%2048].taken = 1;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor6[addr%2048^history6%2048].taken == 0 && gsharePredictor6[addr%2048^history6%2048].strong == 0)
		gsharePredictor6[addr%2048^history6%2048].strong = 1;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor6[addr%2048^history6%2048].taken == 1 && gsharePredictor6[addr%2048^history6%2048].strong == 1)
		gsharePredictor6[addr%2048^history6%2048].strong = 0;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor6[addr%2048^history6%2048].taken == 1 && gsharePredictor6[addr%2048^history6%2048].strong == 0)
		gsharePredictor6[addr%2048^history6%2048].taken = 0;

	history6 = history6 << 1;
	history6 = history6 & 63;
	if (!strncmp(behavior, "T", 2))
		history6 = history6 | 1;

	if (gsharePredictor7[addr%2048^history7%2048].taken == 1 && !strncmp(behavior, "T", 2)) {
		gshare7bit++;
	}	
	else if(gsharePredictor7[addr%2048^history7%2048].taken == 0 && !strncmp(behavior, "NT", 2)) {
		gshare7bit++;
	}
	if(!strncmp(behavior, "T", 2) && gsharePredictor7[addr%2048^history7%2048].taken == 1 && gsharePredictor7[addr%2048^history7%2048].strong == 0)
		gsharePredictor7[addr%2048^history7%2048].strong = 1;
	else if(!strncmp(behavior, "T", 2) && gsharePredictor7[addr%2048^history7%2048].taken == 0 && gsharePredictor7[addr%2048^history7%2048].strong == 1)
		gsharePredictor7[addr%2048^history7%2048].strong = 0;
	else if(!strncmp(behavior, "T", 2) && gsharePredictor7[addr%2048^history7%2048].taken == 0 && gsharePredictor7[addr%2048^history7%2048].strong == 0)
		gsharePredictor7[addr%2048^history7%2048].taken = 1;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor7[addr%2048^history7%2048].taken == 0 && gsharePredictor7[addr%2048^history7%2048].strong == 0)
		gsharePredictor7[addr%2048^history7%2048].strong = 1;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor7[addr%2048^history7%2048].taken == 1 && gsharePredictor7[addr%2048^history7%2048].strong == 1)
		gsharePredictor7[addr%2048^history7%2048].strong = 0;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor7[addr%2048^history7%2048].taken == 1 && gsharePredictor7[addr%2048^history7%2048].strong == 0)
		gsharePredictor7[addr%2048^history7%2048].taken = 0;

	history7 = history7 << 1;
	history7 = history7 & 127;
	if (!strncmp(behavior, "T", 2))
		history7 = history7 | 1;

	if (gsharePredictor8[addr%2048^history8%2048].taken == 1 && !strncmp(behavior, "T", 2)) {
		gshare8bit++;
	}	
	else if(gsharePredictor8[addr%2048^history8%2048].taken == 0 && !strncmp(behavior, "NT", 2)) {
		gshare8bit++;
	}
	if(!strncmp(behavior, "T", 2) && gsharePredictor8[addr%2048^history8%2048].taken == 1 && gsharePredictor8[addr%2048^history8%2048].strong == 0)
		gsharePredictor8[addr%2048^history8%2048].strong = 1;
	else if(!strncmp(behavior, "T", 2) && gsharePredictor8[addr%2048^history8%2048].taken == 0 && gsharePredictor8[addr%2048^history8%2048].strong == 1)
		gsharePredictor8[addr%2048^history8%2048].strong = 0;
	else if(!strncmp(behavior, "T", 2) && gsharePredictor8[addr%2048^history8%2048].taken == 0 && gsharePredictor8[addr%2048^history8%2048].strong == 0)
		gsharePredictor8[addr%2048^history8%2048].taken = 1;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor8[addr%2048^history8%2048].taken == 0 && gsharePredictor8[addr%2048^history8%2048].strong == 0)
		gsharePredictor8[addr%2048^history8%2048].strong = 1;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor8[addr%2048^history8%2048].taken == 1 && gsharePredictor8[addr%2048^history8%2048].strong == 1)
		gsharePredictor8[addr%2048^history8%2048].strong = 0;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor8[addr%2048^history8%2048].taken == 1 && gsharePredictor8[addr%2048^history8%2048].strong == 0)
		gsharePredictor8[addr%2048^history8%2048].taken = 0;

	history8 = history8 << 1;
	history8 = history8 & 255;
	if (!strncmp(behavior, "T", 2))
		history8 = history8 | 1;

	if (gsharePredictor9[addr%2048^history9%2048].taken == 1 && !strncmp(behavior, "T", 2)) {
		gshare9bit++;
	}	
	else if(gsharePredictor9[addr%2048^history9%2048].taken == 0 && !strncmp(behavior, "NT", 2)) {
		gshare9bit++;
	}
	if(!strncmp(behavior, "T", 2) && gsharePredictor9[addr%2048^history9%2048].taken == 1 && gsharePredictor9[addr%2048^history9%2048].strong == 0)
		gsharePredictor9[addr%2048^history9%2048].strong = 1;
	else if(!strncmp(behavior, "T", 2) && gsharePredictor9[addr%2048^history9%2048].taken == 0 && gsharePredictor9[addr%2048^history9%2048].strong == 1)
		gsharePredictor9[addr%2048^history9%2048].strong = 0;
	else if(!strncmp(behavior, "T", 2) && gsharePredictor9[addr%2048^history9%2048].taken == 0 && gsharePredictor9[addr%2048^history9%2048].strong == 0)
		gsharePredictor9[addr%2048^history9%2048].taken = 1;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor9[addr%2048^history9%2048].taken == 0 && gsharePredictor9[addr%2048^history9%2048].strong == 0)
		gsharePredictor9[addr%2048^history9%2048].strong = 1;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor9[addr%2048^history9%2048].taken == 1 && gsharePredictor9[addr%2048^history9%2048].strong == 1)
		gsharePredictor9[addr%2048^history9%2048].strong = 0;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor9[addr%2048^history9%2048].taken == 1 && gsharePredictor9[addr%2048^history9%2048].strong == 0)
		gsharePredictor9[addr%2048^history9%2048].taken = 0;

	history9 = history9 << 1;
	history9 = history9 & 511;
	if (!strncmp(behavior, "T", 2))
		history9 = history9 | 1;

	if (gsharePredictor10[addr%2048^history10%2048].taken == 1 && !strncmp(behavior, "T", 2)) {
		gshare10bit++;
	}	
	else if(gsharePredictor10[addr%2048^history10%2048].taken == 0 && !strncmp(behavior, "NT", 2)) {
		gshare10bit++;
	}
	if(!strncmp(behavior, "T", 2) && gsharePredictor10[addr%2048^history10%2048].taken == 1 && gsharePredictor10[addr%2048^history10%2048].strong == 0)
		gsharePredictor10[addr%2048^history10%2048].strong = 1;
	else if(!strncmp(behavior, "T", 2) && gsharePredictor10[addr%2048^history10%2048].taken == 0 && gsharePredictor10[addr%2048^history10%2048].strong == 1)
		gsharePredictor10[addr%2048^history10%2048].strong = 0;
	else if(!strncmp(behavior, "T", 2) && gsharePredictor10[addr%2048^history10%2048].taken == 0 && gsharePredictor10[addr%2048^history10%2048].strong == 0)
		gsharePredictor10[addr%2048^history10%2048].taken = 1;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor10[addr%2048^history10%2048].taken == 0 && gsharePredictor10[addr%2048^history10%2048].strong == 0)
		gsharePredictor10[addr%2048^history10%2048].strong = 1;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor10[addr%2048^history10%2048].taken == 1 && gsharePredictor10[addr%2048^history10%2048].strong == 1)
		gsharePredictor10[addr%2048^history10%2048].strong = 0;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor10[addr%2048^history10%2048].taken == 1 && gsharePredictor10[addr%2048^history10%2048].strong == 0)
		gsharePredictor10[addr%2048^history10%2048].taken = 0;

	history10 = history10 << 1;
	history10 = history10 & 1023;
	if (!strncmp(behavior, "T", 2))
		history10 = history10 | 1;

	if (gsharePredictor11[addr%2048^history11%2048].taken == 1 && !strncmp(behavior, "T", 2)) {
		gshare11bit++;
	}	
	else if(gsharePredictor11[addr%2048^history11%2048].taken == 0 && !strncmp(behavior, "NT", 2)) {
		gshare11bit++;
	}
	if(!strncmp(behavior, "T", 2) && gsharePredictor11[addr%2048^history11%2048].taken == 1 && gsharePredictor11[addr%2048^history11%2048].strong == 0)
		gsharePredictor11[addr%2048^history11%2048].strong = 1;
	else if(!strncmp(behavior, "T", 2) && gsharePredictor11[addr%2048^history11%2048].taken == 0 && gsharePredictor11[addr%2048^history11%2048].strong == 1)
		gsharePredictor11[addr%2048^history11%2048].strong = 0;
	else if(!strncmp(behavior, "T", 2) && gsharePredictor11[addr%2048^history11%2048].taken == 0 && gsharePredictor11[addr%2048^history11%2048].strong == 0)
		gsharePredictor11[addr%2048^history11%2048].taken = 1;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor11[addr%2048^history11%2048].taken == 0 && gsharePredictor11[addr%2048^history11%2048].strong == 0)
		gsharePredictor11[addr%2048^history11%2048].strong = 1;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor11[addr%2048^history11%2048].taken == 1 && gsharePredictor11[addr%2048^history11%2048].strong == 1)
		gsharePredictor11[addr%2048^history11%2048].strong = 0;
	else if(!strncmp(behavior, "NT", 2) && gsharePredictor11[addr%2048^history11%2048].taken == 1 && gsharePredictor11[addr%2048^history11%2048].strong == 0)
		gsharePredictor11[addr%2048^history11%2048].taken = 0;

	history11 = history11 << 1;
	history11 = history11 & 2047;
	if (!strncmp(behavior, "T", 2))
		history11 = history11 | 1;
}
void tournament(){

	gshareTrue = 0;
	bimodalTrue = 0;
	
	if (gshareP[addr%2048^history12%2048].taken == 1 && !strncmp(behavior, "T", 2)) {
		gshareTrue = 1;
	}	
	else if(gshareP[addr%2048^history12%2048].taken == 0 && !strncmp(behavior, "NT", 2)) {
		gshareTrue = 1;
	}
	if(!strncmp(behavior, "T", 2) && gshareP[addr%2048^history12%2048].taken == 1 && gshareP[addr%2048^history12%2048].strong == 0)
		gshareP[addr%2048^history12%2048].strong = 1;
	else if(!strncmp(behavior, "T", 2) && gshareP[addr%2048^history12%2048].taken == 0 && gshareP[addr%2048^history12%2048].strong == 1)
		gshareP[addr%2048^history12%2048].strong = 0;
	else if(!strncmp(behavior, "T", 2) && gshareP[addr%2048^history12%2048].taken == 0 && gshareP[addr%2048^history12%2048].strong == 0)
		gshareP[addr%2048^history12%2048].taken = 1;
	else if(!strncmp(behavior, "NT", 2) && gshareP[addr%2048^history12%2048].taken == 0 && gshareP[addr%2048^history12%2048].strong == 0)
		gshareP[addr%2048^history12%2048].strong = 1;
	else if(!strncmp(behavior, "NT", 2) && gshareP[addr%2048^history12%2048].taken == 1 && gshareP[addr%2048^history12%2048].strong == 1)
		gshareP[addr%2048^history12%2048].strong = 0;
	else if(!strncmp(behavior, "NT", 2) && gshareP[addr%2048^history12%2048].taken == 1 && gshareP[addr%2048^history12%2048].strong == 0)
		gshareP[addr%2048^history12%2048].taken = 0;

	history12 = history12 << 1;
	history12 = history12 & 2047;
	if (!strncmp(behavior, "T", 2))
		history12 = history12 | 1;

	if (bimodalP[addr%2048].taken == 1 && !strncmp(behavior, "T", 2)) {
		bimodalTrue = 1;
	}	
	else if(bimodalP[addr%2048].taken == 0 && !strncmp(behavior, "NT", 2)) {
		bimodalTrue = 1;
	}
	if(!strncmp(behavior, "T", 2) && bimodalP[addr%2048].taken == 1 && bimodalP[addr%2048].strong == 0)
		bimodalP[addr%2048].strong = 1;
	else if(!strncmp(behavior, "T", 2) && bimodalP[addr%2048].taken == 0 && bimodalP[addr%2048].strong == 1)
		bimodalP[addr%2048].strong = 0;
	else if(!strncmp(behavior, "T", 2) && bimodalP[addr%2048].taken == 0 && bimodalP[addr%2048].strong == 0)
		bimodalP[addr%2048].taken = 1;
	else if(!strncmp(behavior, "NT", 2) && bimodalP[addr%2048].taken == 0 && bimodalP[addr%2048].strong == 0)
		bimodalP[addr%2048].strong = 1;
	else if(!strncmp(behavior, "NT", 2) && bimodalP[addr%2048].taken == 1 && bimodalP[addr%2048].strong == 1)
		bimodalP[addr%2048].strong = 0;
	else if(!strncmp(behavior, "NT", 2) && bimodalP[addr%2048].taken == 1 && bimodalP[addr%2048].strong == 0)
		bimodalP[addr%2048].taken = 0;

	if (selector[addr%2048] == 0 || selector[addr%2048] == 1){
		if (gshareTrue){
			tournamentCount++;
		}
	} 
	else if(selector[addr%2048] == 2 || selector[addr%2048] == 3){
		if (bimodalTrue){
			tournamentCount++;
		}
	}
	if (bimodalTrue && !gshareTrue && selector[addr%2048] < 3) {
			selector[addr%2048]++;
	}
	else if(!bimodalTrue && gshareTrue && selector[addr%2048] > 0){
			selector[addr%2048]--;
	}
}


int main(int argc, char *argv[]) {

	int nt = 0;
	int t = 0;
	int total = 0;
	// Temporary variables
	
	int i;
	
	for (i = 0; i < 16; i++){
		predictor16[i] = 1;
		Predictor* newPredictor = makePredictor();	
		bpredictor16[i] = *newPredictor;
	}
	for (i = 0; i < 32; i++){
		predictor32[i] = 1;
		Predictor* newPredictor = makePredictor();	
		bpredictor32[i] = *newPredictor;
	}
	for (i = 0; i < 128; i++){
		predictor128[i] = 1;
		Predictor* newPredictor = makePredictor();	
		bpredictor128[i] = *newPredictor;
	}
	for (i = 0; i < 256; i++){
		predictor256[i] = 1;
		Predictor* newPredictor = makePredictor();	
		bpredictor256[i] = *newPredictor;
	}
	for (i = 0; i < 512; i++){
		predictor512[i] = 1;
		Predictor* newPredictor = makePredictor();	
		bpredictor512[i] = *newPredictor;
	}
	for (i = 0; i < 1024; i++){
		predictor1024[i] = 1;
		Predictor* newPredictor = makePredictor();	
		bpredictor1024[i] = *newPredictor;
	}
	for (i = 0; i < 2048; i++){
		predictor2048[i] = 1;
		Predictor* newPredictor = makePredictor();	
		bpredictor2048[i] = *newPredictor;
		Predictor* newPredictor2 = makePredictor();
		Predictor* newPredictor3 = makePredictor();
		Predictor* newPredictor4 = makePredictor();
		gsharePredictor3[i] = *newPredictor2;
		gsharePredictor4[i] = *newPredictor2;
		gsharePredictor5[i] = *newPredictor2;
		gsharePredictor6[i] = *newPredictor2;
		gsharePredictor7[i] = *newPredictor2;
		gsharePredictor8[i] = *newPredictor2;
		gsharePredictor9[i] = *newPredictor2;
		gsharePredictor10[i] = *newPredictor2;
		gsharePredictor11[i] = *newPredictor2;
		gshareP[i] = *newPredictor3;
		bimodalP[i] = *newPredictor4;
		selector[i] = 0;
	}

	// Open file for reading
	FILE *input = fopen(argv[1], "r");
	FILE *output = fopen("output.txt", "w");

	// The following loop will read a hexadecimal number and
	// a string each time and then output them
	while(fscanf(input, "%llx %10s\n", &addr, behavior) != EOF) {
		if(!strncmp(behavior, "T", 2)) {
			//printf("%lld -> taken\n", addr);
			t++;
		}
		else {
			//printf("%lld -> not taken\n", addr);
			nt++;
		}
		bimodal1();
		bimodal2();
		gshare();
		tournament();
		total++;
	}
	//printf("%d", total);
	fprintf(output, "%d,%d;\n", t, total);
	fprintf(output, "%d,%d;\n", nt, total);
	fprintf(output, "%d,%d; %d,%d; %d,%d; %d,%d; %d,%d; %d,%d; %d,%d;\n", correct16, total, correct32, total, correct128, total, correct256, total, correct512, total, correct1024, total, correct2048, total);
	fprintf(output, "%d,%d; %d,%d; %d,%d; %d,%d; %d,%d; %d,%d; %d,%d;\n", bcorrect16, total, bcorrect32, total, bcorrect128, total, bcorrect256, total, bcorrect512, total, bcorrect1024, total, bcorrect2048, total);
	fprintf(output, "%d,%d; %d,%d; %d,%d; %d,%d; %d,%d; %d,%d; %d,%d; %d,%d; %d,%d;\n", gshare3bit, total, gshare4bit, total, gshare5bit, total, gshare6bit, total, gshare7bit, total, gshare8bit, total, gshare9bit, total, gshare10bit, total, gshare11bit, total);
	fprintf(output, "%d,%d;\n", tournamentCount, total); 
	
	fclose(output);
	
	return 0;
}
