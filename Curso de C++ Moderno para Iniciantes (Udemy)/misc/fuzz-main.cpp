// Compile with: g++ fuzz-main.cpp -lncurses -ltinfo -o fuzz-his

#ifdef _WIN32
#include <curses.h>
#include <windows.h>
#else
#include <ncurses.h>
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <locale.h>

std::vector<std::string> load_suggestions(const std::string& filename){
  std::vector<std::string> result = {};
  std::ifstream file(filename);
  std::string line = {};
  while(std::getline(file, line)){
    if(!line.empty()) result.push_back(line);
  }
  return result;
}

std::vector<std::string> get_matches(const std::string& input,
    std::vector<std::string> suggestions){
  std::vector<std::string> matches;
  for(const auto& word : suggestions){
    //if(word.find(input) == 0) matches.push_back(word);
    if(word.find(input) != std::string::npos) matches.push_back(word);
  }
  return matches;
}

int main(){	
  setlocale(LC_ALL, "");
  initscr();
  noecho();
  keypad(stdscr, TRUE);
  std::string input;
  int ch;
  int rows, cols;

  std::string home = {}, his_comm = {}, command = {};

  start_color();
  use_default_colors();
  init_pair(99, COLOR_YELLOW, -1);

#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
  home = std::getenv("APPDATA");
  his_comm = home + "\\Microsoft\\Windows\\PowerShell\\PSReadLine\\ConsoleHost_history.txt";
#else
  home = std::getenv("HOME");
  his_comm = home + "/.bash_history";
#endif

  auto suggestions = load_suggestions(his_comm);

  while(true){
    getmaxyx(stdscr, rows, cols);
    clear();

    auto matches = get_matches(input, suggestions);

    if(!matches.empty()){
      command = matches[0];
    }else{
      command.clear();
    }

    for(size_t i = 0; i < matches.size() && i < (size_t)(rows - 1); ++i){
      mvprintw(i, 0, "%s", matches[i].c_str());
    }

    attron(A_BOLD | COLOR_PAIR(99));
    mvprintw(rows - 1, 0, "~> %s", input.c_str());
    attroff(A_BOLD | COLOR_PAIR(99));
    move(rows - 1, 3 + input.size());

    refresh();

    ch = getch();
    if(ch == '\n' || ch == KEY_ENTER){
      endwin();
      if(!input.empty()){
        int ret = std::system(command.c_str());
        if(ret != 0){
          printf("Falha ao executar o comando.\n");
          return -1;
        }
      }
      return 0;
    }


    if(ch == KEY_BACKSPACE || ch == 127 || ch == 8){
      if(!input.empty()) input.pop_back();
    }else if(isprint(ch)){
      input += (char)ch;
    }
  }
}
