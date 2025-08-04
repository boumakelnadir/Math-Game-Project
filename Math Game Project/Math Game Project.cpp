#include <iostream>

using namespace std;

enum enQuestionsLevel{ Easy , Medium , Hard , MixLevel };
enum enOperationType { Add, Sub ,Mult , Div , MixType};
enum enAnswerQuestion{ Right, Wrong };

short ReadPositiveNumber(string message,short from ,short to)
{
	short Q;
	do
	{
		cout << message;
		cin >> Q;

	} while (Q < from || Q > to);
	return Q;
}

short RandomNumber(short from, short to)
{
	short Random = rand() % (to - from + 1) + from;
	return Random;
}

struct stGameResult {
	short NumberOfQuestions = 0;
	enQuestionsLevel QuestionsLevel;
	enOperationType OperationType;
	short NumberOfRightAnswer = 0;
	short NumberOfWrongAnswer = 0;
};

enQuestionsLevel QuestionLevel()
{
	short QuestionLevel = ReadPositiveNumber("Enter Questions Level [1] Easy ,[2] Med , [3] Hard , [4] Mix :",1,4);
	return (enQuestionsLevel)(QuestionLevel - 1);
}

enOperationType OperaType()
{
	short QuestionType = ReadPositiveNumber("Enter Operations Type [1] Add ,[2] Sub , [3] Mult ,[4] Div ,[5] Mix :", 1, 5);
	return (enOperationType)(QuestionType - 1);
}

struct stRoundResult 
{
	short NumberOfQuestions = 0;
	enQuestionsLevel QuestionsLevel;
	enOperationType OperationType;
};

short ShowOperationCalc(string OperType,short Num1,short Num2)
{
	if (OperType == "+")
	{
		cout << Num1 << endl;
		cout << Num2 << " +" << endl;
		cout << "---------------" << endl;
		return Num1 + Num2;
	}
	else if (OperType == "-")
	{
		cout << Num1 << endl;
		cout << Num2 << " -" << endl;
		cout << "---------------" << endl;
		return Num1 - Num2;
	}
	else if (OperType == "*")
	{
		cout << Num1 << endl;
		cout << Num2 << " x" << endl;
		cout << "---------------" << endl;
		return Num1 * Num2;
	}
	else 
	{
		cout << Num1 << endl;
		cout << Num2 << " /" << endl;
		cout << "---------------" << endl;
		return (Num1 / Num2);
	}


}

string MixOperations()
{
	string arrTypeOperation[4] = { "+" ,"-" ,"*" ,"/" };
	return arrTypeOperation[RandomNumber(0, 3)];
}

short OperationLevel(enOperationType Operation,short from,short to)
{ 
	short Num1 = RandomNumber(from,to),
		  Num2 = RandomNumber(from,to);
	
	switch(Operation)
	{ 
	case enOperationType::Add:
		return	ShowOperationCalc("+",Num1,Num2);

	case enOperationType::Sub:
		return	ShowOperationCalc("-", Num1, Num2);

	case enOperationType::Mult:
		return	ShowOperationCalc("*", Num1, Num2);

	case enOperationType::Div:
		return	ShowOperationCalc("/", Num1, Num2);

	case enOperationType::MixType:
		return	ShowOperationCalc(MixOperations(), Num1, Num2);
	
	
	}
	return 0;
	}

short ShowOperations(stRoundResult RoundResult)
{
	switch (RoundResult.QuestionsLevel)
	{
	case enQuestionsLevel::Easy:
		return OperationLevel(RoundResult.OperationType,1,20);

	case enQuestionsLevel::Medium:
		return OperationLevel(RoundResult.OperationType, 20, 60);

	case enQuestionsLevel::Hard:
		return OperationLevel(RoundResult.OperationType, 30, 100);

	case enQuestionsLevel::MixLevel:
		return OperationLevel(RoundResult.OperationType, 1, 100);
	}
}

short AnswerQuestions()
{
	short Number;

	cin >> Number;

	return Number;
}

stGameResult FillGameResult(stRoundResult RoundResult, short NumberOfQuestions, short NumberOfRightAnswer, short NumberOfWrongAnswer)
{
	stGameResult GameResult;
	GameResult.NumberOfQuestions = NumberOfQuestions;
	GameResult.QuestionsLevel = RoundResult.QuestionsLevel;
	GameResult.OperationType = RoundResult.OperationType;
	GameResult.NumberOfRightAnswer = NumberOfRightAnswer;
	GameResult.NumberOfWrongAnswer = NumberOfWrongAnswer;

	return GameResult;
}

enAnswerQuestion ComparedResult(short Question, short Answer)
{
	if (Question == Answer)
		return enAnswerQuestion::Right;
	else
		return enAnswerQuestion::Wrong;
}

stGameResult PlayGame(short HowManyQuestions)
{
	stRoundResult RoundResult;

	short NumberOfRightAnswer = 0, NumberOfWrongAnswer = 0;
	
	RoundResult.QuestionsLevel = QuestionLevel();
	RoundResult.OperationType = OperaType();

	for (short GameRound = 1; GameRound <= HowManyQuestions; GameRound++)
	{
		
		cout << "\nQuestion [" << GameRound << "/" << HowManyQuestions << "]" << endl;
		RoundResult.NumberOfQuestions = GameRound;
	
		short Question =  ShowOperations(RoundResult);
		short Answer = AnswerQuestions();

		if (ComparedResult(Question, Answer) == enAnswerQuestion::Right)
		{
			system("color 2F");
			cout << "Right Answer :-)\n" << endl;
			NumberOfRightAnswer++;
		}
		else {
			system("color 4F");
			cout << "Wrong Answer :-(" << endl;
			cout << "The Answer is : " << Question << endl << endl;
			NumberOfWrongAnswer++;
		}
		
	}
	return FillGameResult(RoundResult,HowManyQuestions,NumberOfRightAnswer,NumberOfWrongAnswer);
}

string QuestionLevelName(enQuestionsLevel QuestionLevel)
{
	string arrQuestionsLevel[4] = { "Easy" , "Medium" , "Hard" , "Mix" };
	return arrQuestionsLevel[(int)QuestionLevel];
}

string OperationTypeName(enOperationType OperaType)
{
	string arrQuestionsLevel[5] = { "Add", "Sub" ,"Mult" , "Div" , "Mix" };
	return arrQuestionsLevel[(int)OperaType ];
}
 
void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void ShowFinalResult(stGameResult GameResult)
{
	short RightAnswer = GameResult.NumberOfRightAnswer,
		  WrongAnswer = GameResult.NumberOfWrongAnswer;

	string result = "";
	cout << "\n--------------------------------" << endl;
	if (RightAnswer == WrongAnswer) {
		result = "Draw";
		system("color 6F");
	}
	else if (RightAnswer > WrongAnswer) {
		result = "Pass :-)";
		system("color 2F");
	}else
		  {
			result = "Failed";
			system("color 4F");
			cout << "\a";
		}

	cout << "Final Result is "<<result << endl;
	cout << "--------------------------------\n" << endl;

}

void ShowFinalCardResult(stGameResult GameResult)
{
	cout << "Number of Questions : " << GameResult.NumberOfQuestions << endl;

	cout << "Questions Level     : " << QuestionLevelName(GameResult.QuestionsLevel) << endl;

	cout << "Operations Type     : " << OperationTypeName(GameResult.OperationType) << endl;

	cout << "Number of Right Answer : " << GameResult.NumberOfRightAnswer << endl;
	cout << "Number of Wrong Answer : " << GameResult.NumberOfWrongAnswer << endl;
	cout << "\n----------------------------------------------" << endl;
}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();

		stGameResult GameResult = PlayGame(ReadPositiveNumber("How Many Questions Do You Want To Answer (1 - 10) : ",1,10));

		ShowFinalResult(GameResult);
		ShowFinalCardResult(GameResult);


		cout << "Do you Want Play Again Y/N : ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');



}




int main()
{
	srand((unsigned)time(0));
	StartGame();



	return 0;
}

