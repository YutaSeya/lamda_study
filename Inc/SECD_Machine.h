#pragma once

#define _MACHINE_DEBUG 0

#include <algorithm>
#include <iostream>
#include <list>
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
  SECDStack D;
  std::string input_lambda_eq;

 public:
  /**
   * @brief コンストラクタ
   */
  SECDMachine() {}

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
#if 0
  std::string createEnvironmentEntry(std::string c1, std::string c2) {
    std::string entry;
    return entry;
  }
#endif

  /**
   * @brief 引数である環境に同じく引数であるエントリーを追加する関数
   * @fn derive
   */

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
    D.printList("D");
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
        is_ap = true;
      } else {
        // 実引数としてロード
        S.inputListBack(C.getHead());
      }

    } else {
      // closure 閉じた関数としてSにロードする
      lambda.buildConstructclosure(C.getHead());
    }
    C.deleteListHead();
    printMachineState();
    return is_ap;
  }
};
