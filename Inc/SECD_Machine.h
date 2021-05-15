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
   * @details ラムダ式の環境変数、ラムダ式の仮引数、実引数の順で文字列を返す
   */
  std::string createEnvironmentEntry(const std::string c1,
                                     const std::string c2) {
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
    // Dに現在のスタックの情報を一時保存
    D.push_back(C);
    D.push_back(E);
    D.push_back(S);

    // 環境変数などをスタックに追加　　

    std::string environment_entry;
    environment_entry = "< " + lm_relate + " = " + c2 + " >";
    E.inputListBack(environment_entry);
    C.inputListBack(lm_arg);

    std::string use_string_array;
    use_string_array = lm_relate + "," + lm_arg + "," + c2;
    return use_string_array;
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
      // データのコピーをしてから表示処理を行う
      std::cout << "D : [ ";
      for (int i = D.size() - 1; i >= 0; i--) {
        if (i == 0) {
          std::cout << D[i].getPrintListString();
        } else {
          std::cout << D[i].getPrintListString() << ", ";
        }
      }
      std::cout << " ]" << std::endl;
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
        C.deleteListHead();
        is_ap = true;

      } else {
        // 実引数としてロード
        S.inputListBack(C.getHead());
        C.deleteListHead();
        printMachineState();
      }

    } else {
      // closure 閉じた関数としてSにロードする
      std::string closure_str = lambda.buildConstructclosure(C.getHead());
      // std::cout << closure_str << std::endl;
      S.inputListFront(closure_str);
      C.deleteListHead();
      printMachineState();
    }

    return is_ap;
  }

  /**
   * @brief コマンドの読み込み処理を連続的に行う
   */
  bool executeToLoadIdentifier() {
    bool is_complete = false;
    while (!loadIdentifierS())
      ;

    // 環境の構築
    std::string str1 = S.getListFirst();
    std::string str2 = S.getListSecond();
    S.deleteListHead();
    S.deleteListHead();

    std::string lambdaeq_param = createEnvironmentEntry(str1, str2);
    printMachineState();

    // 環境変数の処理の実行
    // ラムダ式の文字列を取得するための前処理
    std::replace(lambdaeq_param.begin(), lambdaeq_param.end(), ',', ' ');
    std::istringstream iss(lambdaeq_param);
    // ラムダ式の文字列を取得用変数
    std::string lm_relate, lm_arg, real_arg;
    // 取得処理
    iss >> lm_relate >> lm_arg >> real_arg;
    // 環境変数のデータを書き換え
    if (lm_relate == lm_arg) {
      // λx.xのようなとき
      C.deleteListHead();
      S.inputListBack(real_arg);
    } else {
      // λx.yのようなとき
      C.deleteListHead();
      S.inputListBack(lm_arg);
    }

    printMachineState();
    // 環境変数の処理が終わったため削除
    E.deleteListHead();
    // stackの内容を戻す
    if (D.size() == 4) {
      if (!D[3].isNull()) {
        for (size_t i = 0; i < D[3].getListSize(); i++) {
          C.inputListBack(D[3].getHead());
          D[3].deleteListHead();
        }
      }

      if (!D[2].isNull()) {
        for (size_t i = 0; i < D[2].getListSize(); i++) {
          E.inputListBack(D[2].getHead());
          D[2].deleteListHead();
        }
      }

      if (!D[1].isNull()) {
        for (size_t i = 0; i < D[1].getListSize(); i++) {
          E.inputListBack(D[1].getHead());
          D[1].deleteListHead();
        }
      }

      D.clear();
      SECDStack D_buff;
      D_buff.inputListBack("D0");
      D.push_back(D_buff);
    }

    printMachineState();

    if (C.isNull()) is_complete = true;

    return is_complete;
  }
};
