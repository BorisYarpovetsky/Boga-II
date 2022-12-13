#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){
	// Печать в консоли заголовока с названием игры и авторства
	printf("%25s","BOGA II\n");
	printf("%30s","CREATIVE COMPUTING\n");
	printf("%35s","MORRISTOWN, NEW JERSEY\n\n\n");

	char Q[256]; // Определение переменной для ввода строки пользователем и печати сетки игрового поля

	// Вопрос в консоли: Хочет ли игрок прочесть правила игры?
	printf("DO YOU WANT INSTRUCTIONS? ");
	scanf("%s",Q);
	printf("\n\n");

    if (Q[0]=='Y' || Q[0]=='y') {
		// Печать в консоли правил игры
		printf("  THE BOGA IS HIDING ON A GRID (YOU SPECIFY THE LENGTH\n");
		printf("AND WIDTH). TRY TO GUESS HIS POSITION USING THE HINTS\n");
		printf("I GIVE YOU.  EACH GUESS IS TWO NUMBERS SEPERATED BY\n");
		printf("A COMMA.  PLEASE KEEP IN MIND THAT THE BOGA IS ALSO\n");
		printf("SEARCHING FOR YOU!!!!\n\n\n");
	}
	// Определение целых перемнных
	int U,Counter,F,Grid,I,J,Flag,BogaStep;

	// Переменные для начального положения и угадывания координат Игрока и Боги
	struct Positions {
		int X, Y, GX, GY;
	};

	struct Positions Player,Boga;

do { // Основной цикл

	U=0; // Счётчик ходов Боги
	Counter=1; // Счётчик ходов игрового сеанса (непонятно, почему начинается с еденицы)
	F=0; // Счётчик ходов игрока

	do {	// Вопрос в консоли: Насколько велика будет сетка игрового поля (20 максимум)?
		printf("\nHOW BIG SHOULD THE GRID BE(20 MAXIMUM)? ");
		scanf("%d",&Grid);
		getchar();
	}while  (Grid>20 || Grid<1);
	printf("\n");

	// Вопрос в консоли: Напечатать ли в консоли образец сетки?
	strcpy(Q,"");
	printf("WOULD YOU LIKE A SAMPLE GRID? ");
	scanf("%s",Q);
	if (Q[0]=='Y' || Q[0]=='y'){
		printf("\n");
		// Если размер сетки больше или равен 10, то вначале печатаем дополнительную строку старших десятичных разрядов номеров сетки в консоль для столбцов от 10 до 20
		if (Grid>=10) {
            printf("%24s","");//tab(25);
			for (I=10;I<=Grid;I++){
				J=round(I/10);
				printf("%d ",J);
            }
            printf("\n");
		}
		// Печатаем в консоль сетку
		printf("%4s","");//tab(5);
		for (I=0;I<=Grid;I++){
			J=I-round(I/10)*10;
			printf("%d ",J);// Генерация строки номеров младших десятичных разрядов  (значения могут быть только от 0 до 9)
		}
        printf("\n");
		strcpy(Q,""); // Очищаем строковую переменную Q
		for (I=0; I<=Grid; I++){
			strcat(Q,"* "); // Генерация строки из символов "*" и пробелов в строку, и запись её в строковую переменную Q, в соответствии с переменной размера сетки Grid
		}
		for (I=0; I<=Grid; I++){
			printf(" %-3d%s\n",I,Q); // Печать сгенерированных в перыдущем цикле строк в консоль, в соответствии с переменной размера сетки Grid
		}
	}

    printf("\n");
	Flag=1; // Устанавливаем переменную запуска нового сеанса игры = 1

	do{
        strcpy(Q,"");
		printf("\nCHOOSE YOUR POSITION ");
		scanf("%d%c%d",&Player.X,Q,&Player.Y); // Ввод начальных координат Игрока. X1 и Y1 в исходнике на BASIC
        getchar();
	}while (Player.X>Grid || Player.X<0 || Player.Y>Grid || Player.Y<0 || Q[0]!=','); // Цикл, пока координаты не будут заданы в пределах размеров сетки (Grid)

	// Генерация случайной позиции Боги в пределах сетки игрового поля
	printf("\nTHE BOGA PICKS HIS POSITION!\n");
	Boga.X = rand()%(Grid+1); // Получаем случайные координаты Боги в диапазоне от 0 до размера сетки игрового поля (целочисленный остаток от деления значения из функции rand() на размер сетки+1)
	Boga.Y = rand()%(Grid+1);
    //printf("%d,%d\n",Boga.X,Boga.Y); // Печать координат Боги для отладки игры

	while  (Counter<10) { // Цикл сеанса игры
		do {
            strcpy(Q,"");
			printf("\nGUESS #%d ",Counter); // Печать в консоль предложения игроку угадать координаты Боги и печать текущего хода
			scanf("%d%c%d",&Player.GX,Q,&Player.GY); // Ввод игроком предполагаемых координат Боги
			getchar();
		} while (Player.GX>Grid || Player.GX<0 || Player.GY>Grid || Player.GY<0 || Q[0]!=','); // Если введённые значения вне сетки игрового поля, то предлагаем ввести их заново
		Counter=Counter+1;
		F=F+1;

		if (Player.GX==Boga.X && Player.GY==Boga.Y) {  //Если игрок указал верные координаты Боги, то сообщаем об этом, и выходим и цикла сеанса игры в основной цикл
			printf("YOU GUESSED THE BOGA'S POSITION IN %d GUESS(ES)!\n",F);
			break;
        }

		printf("\nYOU GUESSED %d,%d",Player.GX,Player.GY);

		printf("\n\nHE'S MORE TO THE ");

		if (Boga.X==Player.GX && Boga.Y<Player.GY) printf("NORTH"); 	// Бога северней
		if (Boga.X==Player.GX && Boga.Y>Player.GY) printf("SOUTH");  	// Бога южней
		if (Boga.X<Player.GX && Boga.Y==Player.GY) printf("WEST");   	// Бога западней
		if (Boga.X>Player.GX && Boga.Y==Player.GY) printf("EAST");	    // Бога восточней
		if (Boga.X<Player.GX && Boga.Y<Player.GY) printf("NORTHWEST");  // Бога северозападней
		if (Boga.X<Player.GX && Boga.Y>Player.GY) printf("SOUTHWEST");  // Бога югозападней
		if (Boga.X>Player.GX && Boga.Y<Player.GY) printf("NORTHEAST");  // Бога северовосточней
		if (Boga.X>Player.GX && Boga.Y>Player.GY) printf("SOUTHEAST");  // Бога юговосточней

	// ИИ Боги

		printf("\n");
		if (Flag==1) { // Если ход первый, Бога начинает угадывать положение игрока из центра сетки игрового поля
			Boga.GX=round(.5*Grid);
			Boga.GY=round(.5*Grid);
		}

		printf("\nTHE BOGA GUESSES %d,%d\n",Boga.GX,Boga.GY); // Печатаем на консоль предполжение Боги касательно координат игрока
		U=U+1; // Увеличиваем счётчик ходов Боги

		if (abs(Player.Y-Boga.GY)+abs(Player.X-Boga.GX)==0) { // Если Бога угадал позицию игрока, то сообщаем об этом, и выходим и цикла сеанса игры в главный цикл
			printf ("\nTHE BOGA GUESSED YOUR POSITION IN %d GUESS(ES)!\n",U);
			break;
		}
		Flag=0; // Устанавливаем переменную запуска нового сеанса игры = 0
	//-------Y-------
		if (Boga.GY!=Player.Y) { // Если координата по Y в предположении Боги неравна положению игрока по Y

            if (abs(Boga.GY-Player.Y) < 2) {
                BogaStep=1; // Если расстояние по Y до игрока меньше 2-х, то переменна шага для следующего хода Боги BogaStep = 1
            } else BogaStep=2; //Иначе шаг BogaStep = 2

			if (Boga.GY<Player.Y) {
                 Boga.GY=abs(Boga.GY+BogaStep); //Если предыдущее предположение Боги по Y меньше Y игрока, то прибавляем шаг по Y
			} else Boga.GY=abs(Boga.GY-BogaStep);  //Иначе, вычитаем шаг из предположения Боги по Y

			if (Boga.GY>Grid)  Boga.GY=.5*Grid; // Если предположение боги по Y больше размеров секти игрового поля, то Y предположения перемещается в центр сетки
		}
		//--------X--------
		if (Boga.GX!=Player.X) { // Если координата по X в предположении Боги неравна положению игрока по X

			if (abs(Boga.GX-Player.X)<2) {
                BogaStep=1; // Если расстояние по X до игрока меньше 2-х, то переменна шага для следующего хода Боги BogaStep = 1
			} else BogaStep=2; //Иначе шаг BogaStep = 2

			if (Boga.GX<Player.X) {
                Boga.GX=abs(Boga.GX+BogaStep); // Если предыдущее предположение Боги по X меньше X игрока, то прибавляем шаг по X
            } else Boga.GX=abs(Boga.GX-BogaStep);  //Иначе, вычитаем шаг из предположения Боги по X

			if (Boga.GX>Grid)  Boga.GX=.5*Grid; // Если предположение боги по X больше размеров секти игрового поля, то X предположения перемещается в центр сетки
		}
	}
	if (Counter>=10) printf("\nYOU USED UP ALL OF YOUR GUESSES.\n"); // Если игрок использовал все ходы, то печатаем об этом сообщение в консоли

	printf("\nTHE BOGA WAS AT %d,%d\n",Boga.X,Boga.Y);

	printf("\nDO YOU WANT TO PLAY AGAIN? "); //Предлагаем сыграть снова

	strcpy(Q,"");

	scanf("%s",Q);
} while (Q[0]=='Y' || Q[0]=='y');

return 0; // Выход из игры
}
