#pragma once

#define _MACHINE_DEBUG 0

#include <algorithm>
#include <iostream>
#include <list>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include "Lambda_Equation.h"
#include "SECD_Stack.h"

class SECDMachine {
 private:
  LambdaEquation lambda;
  SECDStack S;
  SECDStack E;
  SECDStack C;
  std::vector<SECDStack> D;
  std::string input_lambda_eq;

 public:
  /**
   * @brief コンストラクタ
   */
  SECDMachine() {
    SECDStack D_buff;
    D_buff.inputListBack("D0");
    D.push_back(D_buff);
  }

  /**
   * @brief デストラクタ
   */
  ~SECDMachine() {}

  /**
   * @brief 標準入力からラムダ式の入力を求める関数
   */
  bool inputLambdaEquation() {
    std::cout << "lamda : @, varaiable : 1 character" << std::endl;
    std::getline(std::cin, input_lambda_eq);
    // 解析して正しい式かどうかを判定
    bool is_brackets = lambda.checkConsistencyBrackets(input_lambda_eq);
    C.inputListBack(input_lambda_eq);
    return is_brackets;
  }

  /**
   * @brief 2つの引数から環境へのエントリーを作成する関数
   * @fn assoc
   */
  void createEnvironmentEntry(const std::string c1, const std::string c2) {
#if _MACHINE_DEBUG
    std::cout << str1 << std::endl;
    std::cout << str2 << std::endl;
#endif
    // str1からclosureのλ式のデータを取得
    std::string entry;

    // ラムダ式のデータ取得のための処理
    std::string acq = c1.substr(10);
    std::replace(acq.begin(), acq.end(), ',', ' ');
    std::istringstream iss(acq);
    // ラムダ式のデータを取得
    std::string lm_relate;
    std::string lm_arg;

    iss >> lm_relate >> lm_arg;
    // std::cout << lm_relate << ", " << lm_arg << std::endl;
    }

  /**
   * @brief 引数である環境に同じく引数であるエントリーを追加する関数
   * @fn derive
   */
  void entryDerive() {}

  /**
   * @brief 引数であるclosureから環境を抽出する関数
   * @fn environmentpart
   */

  /**
   * @brief 引数であるclosureからabstractionの本体を抽出する関数
   * @fn controlpart
   */

  /**
   * @brief operand、application (𝑀𝑀 𝑁𝑁) から実引数𝑁𝑁を抽出する関数
   * @fn rand
   */
  void extractApplicationActualArgument() {
    // randX: (ratorX:(ap : tC))
    std::vector<std::pair<int, int> > ps;
    std::string sc = C.getHead().substr(1, C.getHead().length() - 2);
    ps = lambda.getConsistencyBracketsPair(sc);
    if (ps.size() == 1) {
      // ()の組み合わせが一つの場合は、実引数が後ろにあることで確定
      std::string actual_var = sc.substr(ps[0].second + 1, sc.size());
      std::string lambda_eq = sc.substr(ps[0].first, ps[0].second + 1);

      C.deleteListHead();
      C.inputListBack(actual_var);
      C.inputListBack(lambda_eq);
      C.inputListBack("ap");

    } else {
      // ()の組み合わせが複数ある場合は、ラムダ式が後ろにもあるはず
    }

#if _MACHINE_DEBUG
    std::cout << sc << std::endl;
    std::cout << actual_var << std::endl;
    std::cout << lambda_eq << std::endl;
#endif
    printMachineState();
  }

  /**
   * @brief operator、application (𝑀𝑀 𝑁𝑁) から関数𝑀𝑀を抽出する関数
   * @fn rator
   */
  // void extractApplicationFunction() {}

  /**
   * @brief マシンの状態を標準出力に出力する
   */
  void printMachineState() {
    std::cout << "------------------------" << std::endl;
    S.printList("S");
    E.printList("E");
    C.printList("C");
    // Dに関しては、表示のプログラムを別途書く必要があり。
    if (D.size() == 1) {
      D[0].printList("D");
    } else {
      for (size_t i = 0; i < D.size(); i++) {
      }
    }
  }

  /**
   * @brief コマンドの読み込みを行い命令内容に変換したものをSを代入する
   */
  bool loadIdentifierS() {
    bool is_ap = false;
    bool idt = lambda.isIdentifier(C.getHead());
    if (idt) {
      // apの場合は処理が変わる
      if (C.getHead() == "ap") {
        // ap命令の実行を指示
        std::cout << "call me" << std::endl;
        std::string str1 = S.getListFirst();
        std::string str2 = S.getListSecond();

        S.deleteListHead();
        S.deleteListHead();
        createEnvironmentEntry(str1, str2);
        is_ap = true;
      } else {
        // 実引数としてロード
        S.inputListBack(C.getHead());
      }

    } else {
      // closure 閉じた関数としてSにロードする
      std::string closure_str = lambda.buildConstructclosure(C.getHead());
      // std::cout << closure_str << std::endl;
      S.inputListFront(closure_str);
    }
    C.deleteListHead();
    printMachineState();
    return is_ap;
  }
};
