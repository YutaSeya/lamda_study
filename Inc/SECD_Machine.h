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
    std::string lm_relate;
    std::string lm_arg;

    // ()が存在するかどうかによってacqの後の処理を変更
    std::vector<std::pair<int, int> > ps;
    ps = lambda.getConsistencyBracketsPair(acq);

    if (ps.size() == 0) {
      std::istringstream iss(acq);
      // ラムダ式のデータを取得
      iss >> lm_relate >> lm_arg;
    } else {
      // ,の前と後でデータを取得する
      // std::cout << ps[0].first << ", " << ps[0].second << std::endl;
      for (int i = 0; i < ps[0].first; i++)
        if (acq.at(i) != ' ') lm_relate += acq[i];

      for (int i = ps[0].first; i < ps[0].second + 1; i++) lm_arg += acq[i];
    }

    // std::cout << acq << ", " << lm_relate << ", " << lm_arg << std::endl;
    // Dに現在のスタックの情報を一時保存
    D.push_back(C);
    D.push_back(E);
    D.push_back(S);

    // 今のスタックのデータは全て削除しないと
    while (!C.isNull()) C.deleteListHead();

    while (!E.isNull()) E.deleteListHead();

    while (!S.isNull()) S.deleteListHead();

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
    if (ps.size() == 0) {
      C.inputListBack(C.getHead());
      C.deleteListHead();
    } else if (ps.size() == 1) {
      // ()の組み合わせが一つの場合は、実引数があるときとないときがあり得る
      std::string actual_var = sc.substr(ps[0].second + 1, sc.length());

      if (actual_var.length() == 0) {
        C.inputListBack(C.getHead());
        C.deleteListHead();
      } else {
        // actual_varにデータが入ってないときと入っているときで処理を変更
        std::string lambda_eq = sc.substr(ps[0].first, ps[0].second + 1);
#if _MACHINE_DEBUG
        std::cout << sc << std::endl;
        std::cout << actual_var << std::endl;
        std::cout << lambda_eq << std::endl;
#endif
        C.deleteListHead();
        C.inputListBack(actual_var);
        C.inputListBack(lambda_eq);
        C.inputListBack("ap");
      }

    } else {
      // ()の組み合わせが複数ある場合は、ラムダ式が後ろにもあるはず
      // ()の依存関係を調べて、一つ目の式の外側に()があったらそれを抽出する
      // 入力をしっかりとしないと厳しい
      bool is_outside_lamda = false;
      int start_brackets = ps[0].first;
      int end_brackets = ps[0].second;
      for (int i = 0; i < (int)ps.size(); ++i) {
        // if (i) std::cout << ", ";
        // std::cout << "(" << ps[i].first << ", " << ps[i].second << ")";
        if (end_brackets < ps[i].second) {
          is_outside_lamda = true;
          start_brackets = ps[i].first;
          end_brackets = ps[i].second;
        }
      }
      // std::cout << std::endl;
      // std::cout << start_brackets << " " << end_brackets << std::endl;

      if(is_outside_lamda){
        std::string actual_var = sc.substr(ps[0].second + 2, start_brackets);
        std::string lambda_eq = sc.substr(start_brackets, end_brackets - 1);

        C.deleteListHead();
        C.inputListFront("ap");
        C.inputListFront(actual_var);
        C.inputListFront(lambda_eq);

        sc = C.getHead().substr(1, C.getHead().length() - 2);
        ps = lambda.getConsistencyBracketsPair(sc);
        while (ps.size() > 2) {
          printMachineState();
          C.deleteListHead();
          start_brackets = ps[0].first;
          end_brackets = ps[0].second;
          for (int i = 0; i < (int)ps.size(); ++i) {
            // if (i) std::cout << ", ";
            // std::cout << "(" << ps[i].first << ", " << ps[i].second << ")";
            if (end_brackets < ps[i].second) {
              start_brackets = ps[i].first;
              end_brackets = ps[i].second;
            }
          }

          actual_var = sc.substr(ps[0].first, start_brackets);
          lambda_eq = sc.substr(start_brackets, end_brackets);

          C.inputListFront("ap");
          C.inputListFront(actual_var);
          C.inputListFront(lambda_eq);

          sc = C.getHead().substr(1, C.getHead().length() - 2);
          ps = lambda.getConsistencyBracketsPair(sc);
        }
      } else {
        // ()の組み合わせが一つの場合は、実引数があるときとないときがあり得る
        std::string actual_var = sc.substr(ps[0].second + 1, sc.length());

        if (actual_var.length() == 0) {
          C.inputListBack(C.getHead());
          C.deleteListHead();
        } else {
          // actual_varにデータが入ってないときと入っているときで処理を変更
          std::string lambda_eq = sc.substr(ps[0].first, ps[0].second + 1);
          C.deleteListHead();
          C.inputListBack(actual_var);
          C.inputListBack(lambda_eq);
          C.inputListBack("ap");
        }

      }
    }

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
    // Cレジスタにデータがない場合は終了
    if (C.isNull()) return true;
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

    // ラムダ式の中に()が追加であるときにおかしくなっていますね。どうにかしないとだめそう
    if (S.getListSize() > 1) {
      // 環境の構築
      std::string str1 = S.getListFirst();
      std::string str2 = S.getListSecond();
      S.deleteListHead();
      S.deleteListHead();

      std::string lambdaeq_param = createEnvironmentEntry(str1, str2);
      printMachineState();
      //std::cout << C.getHead() << std::endl;

      // std::cout << lambdaeq_param << std::endl;
      // lambdaeq_paramにカッコがあるかどうかで処理を変えていく
      std::vector<std::pair<int, int> > ps;
      ps = lambda.getConsistencyBracketsPair(C.getHead());

      if(ps.size() == 0){
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
      } else {
        bool is_include_lamda_eq = false;
        std::string check_lamda_eq = C.getHead();
        for(size_t i = 0; i < check_lamda_eq.size(); i++){
          if(check_lamda_eq.at(i) == '@'){
            is_include_lamda_eq = true;
            break;
          }
        }
        if(is_include_lamda_eq){
          // ラムダ式がある場合はこっちかな
          std::string closure_str = lambda.buildConstructclosure(C.getHead(), E.getHead());
          //std::cout << closure_str << std::endl;  
          C.deleteListHead();
          S.inputListBack(closure_str);  
        } else {
          // ラムダ式の文字列を取得用変数
          int string_counter = 0;
          std::vector<std::string> lamda_relate_param;
          lamda_relate_param.resize(4);
          for(size_t i = 0; i < lambdaeq_param.size(); i++){
            if(lambdaeq_param[i] == ','){
              string_counter++;
            } else {
              lamda_relate_param[string_counter] += lambdaeq_param[i];
            }
          }
          // ラムダ式の文字列を取得用変数
          std::string lm_relate, lm_arg, real_arg;
          lm_relate = lamda_relate_param[0];
          lm_arg = lamda_relate_param[1];
          real_arg = lamda_relate_param[2];
          for(size_t i = 0; i < lm_arg.size(); i++){
            if(lm_relate[0] == lm_arg[i]){
              lm_arg[i] = real_arg[0];
            }
          }
          C.deleteListHead();
          S.inputListBack(lm_arg);
        }
      }

      printMachineState();

      // 環境変数の処理が終わったため削除
      E.deleteListHead();

      restoreDTempStoreDataToRegister();
      
    }

    if (C.isNull()) is_complete = true;

    return is_complete;
  }

  /**
   * @brief Dに一時退避したデータをレジスタに戻す
   */
  void restoreDTempStoreDataToRegister() {
    // stackの内容を戻す
    if (D.size() != 0) {
      if (!D[3].isNull()) {
        std::vector<std::string> x = D[3].getPrintListVector();
        for (size_t i = 0; i < x.size(); i++) {
          S.inputListBack(x.at(i));
        }
      }

      if (!D[2].isNull()) {
        std::vector<std::string> x = D[2].getPrintListVector();
        for (size_t i = 0; i < x.size(); i++) {
          E.inputListBack(x.at(i));
        }
      }

      if (!D[1].isNull()) {
        std::vector<std::string> x = D[1].getPrintListVector();
        for (size_t i = 0; i < x.size(); i++) {
          C.inputListBack(x.at(i));
        }
      }

      D.clear();
      SECDStack D_buff;
      D_buff.inputListBack("D0");
      D.push_back(D_buff);
    }

    printMachineState();
  }
};
