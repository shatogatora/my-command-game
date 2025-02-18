#include <stdio.h>

#define MAZE_ROW    5      //迷路の行数
#define MAZE_COLUMN 5      //迷路の列数


//プレイヤー
typedef struct
{
  int row;        //プレイヤー位置(行)
  int column;     //プレイヤー位置(列)
}MazePlayer;


//迷路の一ブロック
enum MazeKind {PATH, WALL, START, GOAL};    //ブロックの種類(道、壁、スタート、ゴール)
enum MazeFlag {FALSE, TRUE};                //ブロックが判明しているかどうか

typedef struct
{
  enum MazeKind kind;            //種類(道、壁、スタート、ゴール)
  enum MazeFlag flag;            //ブロックが判明しているかどうか
} MazeBlock;


//プレイヤー初期化
int MazePlayerInit(int *playerRow, int *playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
  int i, j;

  for(i = 0; i < MAZE_ROW ; i++) //行
  {
    for(j = 0;  j < MAZE_COLUMN; j++) //列
    {
      if(maze[i][j].kind == START) //スタート地点ならばプレイヤーの位置に設定する
      {
        *playerRow    = i;
        *playerColumn = j;
        return 0; //関数終了(プレイヤーを設定できれば残りの処理は必要ない)
      }
    }
  }

  //スタート地点がなければ、プレイヤーを設定できずここまでくる
  printf("スタートがありません\n");
  return -1;
}


//迷路表示
void MazeDraw(int playerRow, int playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
  int i, j;

  for(i = 0; i < MAZE_ROW; i++) //行
  {
    for(j = 0; j < MAZE_COLUMN; j++ ) //列
    {
      if(i == playerRow && j == playerColumn) //プレイヤー位置
      {
        printf("Ｐ");
      }
      else if(maze[i][j].flag == FALSE) //ブロックが判明していない場合
      {
        printf("？");
      }
      else
      {
        switch(maze[i][j].kind)
        {
        case WALL:
          printf("口"); break; //壁
        case GOAL:
          printf("Ｇ"); break; //ゴール
        default:
          printf("　"); break; //その他(道、スタート)
        }
      }
    }
    printf("\n");
  }
}


//方向
enum MazeDirection{UP, DOWN, LEFT, RIGHT, Invalid}; 

//プレイヤー移動
void MazePlayerMove(int *playerRow, int *playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
  char buf[100];
  int  direction = -1;

  printf("%d:上\n", UP);
  printf("%d:下\n", DOWN);
  printf("%d:左\n", LEFT);
  printf("%d:右\n", RIGHT);
  printf("数字を入力してください。：");

  fgets(buf, sizeof(buf), stdin);      //文字列で入力を読み込む
  sscanf(buf, "%d", &direction);        //数字にできる場合は変換(できなければ何もしない)

  while(direction < 0 || direction > (Invalid - 1)) //入力が正しい場合まで繰り返す
  {
    printf("入力が不正です。再入力してください:");
    fgets(buf, sizeof(buf), stdin);
    sscanf(buf, "%d", &direction);
  }


  switch(direction){
    //上移動
  case UP:
  {
    if(*playerRow - 1 >= 0) //迷路の範囲外でないことを確認
    {
      maze[*playerRow - 1][*playerColumn].flag = TRUE; //ブロックの種類が判明

      if(maze[*playerRow - 1][*playerColumn].kind != WALL) //壁かどうか確認
      {
        *playerRow -= 1; //移動
        printf("\n上に移動しました。\n");
      }
      else
      {
        printf("\n壁です。\n");
      }
    }
    else
    {
      printf("\n範囲外です\n");

    }
  }
  break;

  //下移動
  case DOWN:
  {
    if(*playerRow + 1 < MAZE_ROW)
    {
      maze[*playerRow + 1][*playerColumn].flag = TRUE;

      if(maze[*playerRow + 1][*playerColumn].kind != WALL)
      {
        *playerRow += 1;
        printf("\n下に移動しました。\n");
      }
      else
      {
        printf("\n壁です。\n");
      }
    }
    else
    {
      printf("\n範囲外です\n");

    }
  }
  break;

  //左移動
  case LEFT:
  {
    if(*playerColumn - 1 >= 0)
    {
      maze[*playerRow][*playerColumn - 1].flag = TRUE;

      if(maze[*playerRow][*playerColumn - 1].kind != WALL)
      {
        *playerColumn -= 1;
        printf("\n左に移動しました。\n");
      }
      else
      {
        printf("\n壁です。\n");
      }
    }
    else
    {
      printf("\n範囲外です\n");

    }
  }
  break;

  //右移動
  case RIGHT:
  {
    if(*playerColumn + 1 < MAZE_COLUMN)
    {
      maze[*playerRow][*playerColumn + 1].flag = TRUE;

      if(maze[*playerRow][*playerColumn + 1].kind != WALL)
      {
        *playerColumn += 1;
        printf("\n右に移動しました。\n");
      }
      else
      {
        printf("\n壁です。\n");
      }
    }
    else
    {
      printf("\n範囲外です\n");

    }
  }
  break;
  }
}


//ゴール判定
int MazeGoalCheck(int playerRow, int playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
  if(maze[playerRow][playerColumn].kind == GOAL) //プレイヤー位置がゴール地点に等しい
  {
    printf("ゴール!\n");
    return 1;
  }
  return 0;
}


//迷路ゲーム
void MazeGame(void)
{
  //プレイヤー
  MazePlayer player;

  //迷路
  MazeBlock maze[MAZE_ROW][MAZE_COLUMN] = 
    {
      { {START, TRUE } , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE} },
      { {WALL , FALSE} , {WALL , FALSE}, {PATH , FALSE}, {WALL , FALSE}, {WALL , FALSE} },
      { {WALL , FALSE} , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE} },
      { {PATH , FALSE} , {PATH , FALSE}, {WALL , FALSE}, {WALL , FALSE}, {WALL , FALSE} },
      { {WALL , FALSE} , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {GOAL , TRUE } },
    };


  //プレイヤー初期化
  if(MazePlayerInit(&player.row, &player.column, maze) == -1)
  {
    //関数MazePlayerInitが-1を返すとき初期化に失敗している
    //よって、この時点でプログラムを終了し、迷路の表示は行わない
    return;
  }

  while(MazeGoalCheck(player.row, player.column, maze) != 1) //ゴールするまで移動を繰り返す
  {
    //迷路表示
    MazeDraw(player.row, player.column, maze);
    //プレイヤー移動
    MazePlayerMove(&player.row, &player.column, maze);
  }

  //迷路最終結果表示
  MazeDraw(player.row, player.column, maze);
}


//メニュー
enum MazeMenu {STAGE0, EXIT};

//タイトル
int MazeTitle()
{
  char buf[100];
  int menu = -1;

  printf("\n\n＊＊＊迷路ゲーム＊＊＊\n\n");

  printf("メニュー\n");
  printf("%d:ステージ0\n", STAGE0);
  printf("%d:終了\n", EXIT);

  printf("メニューを選んでください。：");

  fgets(buf, sizeof(buf), stdin);
  sscanf(buf, "%d", &menu);

  while(menu < 0 || menu > EXIT)
  {
    printf("入力が不正です。再入力してください:");
    fgets(buf, sizeof(buf), stdin);
    sscanf(buf, "%d", &menu);
  }

  return menu;
}


int main(void)
{
  int menu;

  while(1)
  {
    //メニュー選択      
    menu = MazeTitle();
    printf("\n");

    if(menu == EXIT) //EXITならwhileループを抜けて終了
    {
      break;
    }

    //迷路ゲーム
    MazeGame();

    //ゲームが終わるとwhileループの先頭にもどる
  }

  return 0;
}
