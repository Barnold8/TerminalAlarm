#ifndef UTILS
#define UITLS


int charIsNum(char c) {
  return c < 58 && c > 47;
}

void clearTerminal(){

	printf("\e[1;1H\e[2J"); 
}


#endif
