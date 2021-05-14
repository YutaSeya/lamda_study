#pragma once

#include <stack>
#include <string>
#include <vector>

#include "SECD_Stack.h"

class LambdaEquation {
 private:
 public:
  /**
   * @brief コンストラクタ
   */
  LambdaEquation() {}

  /**
   * @brief デストラクタ
   */
  ~LambdaEquation() {}

  /**
   * @brief 引数が変数であるかどうかを判定する関数
   * @fn identifier
   */
  bool isIdentifier(const std::string c) {
    std::vector<std::pair<int, int> > ps;
    ps = getConsistencyBracketsPair(c);
    if (ps.size() == 0)
      return true;
    else
      return false;
  }

  /**
   * @brief この定義中で使われる構造closureを構築する関数
   * @fn constructclosure
   */
  std::string buildConstructclosure(const std::string c) {
    std::string constructclosure;
    std::vector<std::pair<int, int> > ps;
    ps = getConsistencyBracketsPair(c);
    std::string sc;

    if (ps.size() == 1) {
      sc = c.substr(ps[0].first + 1, ps[0].second - 1);
      // std::cout << "sc = " << sc << std::endl;

      // ラムダの数を数えて、closureを構築する
      // λの関数の記号を取得
      std::string lm_relate;
      // λ関数の環境の記号を取得
      std::string lm_arg;
      for (size_t i = 0; i < sc.size() - 1; i++) {
        if (sc[i] == '@') {
          lm_relate = sc[i + 1];
          lm_arg = sc.substr(i + 3, sc.size());
        }
      }
      // std::cout << lm_relate_buff << std::endl;
      // std::cout << lm_arg_buff << std::endl;
      constructclosure = "< closure " + lm_relate + ", " + lm_arg + ", [ ] >";
    } else {
      // 複数個ある場合は変数が複数あるので、上手く抜き出す必要がある
    }

    return constructclosure;
  }
#if 0
  /**
   * @brief 引数がabstractionであるかどうかを判定する関数
   * @fn lambda exp
   */
  bool isLambdaExp(std::string c) { return false; }

  /**
   * @brief abstractionを引数として束縛変数（𝜆𝑣.𝑀の𝑣）を抽出する関数
   * @fn bv
   */
  std::string extractionBondageVaraiable(std::string c) {
    std::string bv;
    return bv;
  }

  /**
   * @brief abstractionを引数として本体部分（𝜆𝑣.M のM）を抽出する関数
   * @fn body
   */
  std::string extractionBodyVaraiable(std::string c) {
    std::string body;
    return body;
  }



  /**
   * @brief 引数が構造closureであるか否かを判定する関数
   * @fn closure
   */
  bool isClosure(std::string c) { return false; }
#endif

  /**
   * @brief カッコの対応関係のペアができているかの確認
   * @return true:対応関係がある false:対応関係がない
   */
  bool checkConsistencyBrackets(const std::string& c) {
    std::stack<int> st;  // 左括弧の index を格納するスタック
    std::vector<std::pair<int, int> > ps;  // 対応を表すペア

    // ループを回す
    for (int i = 0; i < (int)c.size(); ++i) {
      if (c[i] == '(')
        st.push(i);
      else if (c[i] == ')') {
        if (st.empty()) {
          std::cout << "error" << std::endl;
          return false;
        }
        int t = st.top();
        st.pop();
        ps.push_back({t, i});
      }
    }

    // スタックが空でなかったら左括弧が過剰
    if (!st.empty()) {
      std::cout << "too many (" << std::endl;
      return false;
    }

    // カッコの組み合わせが2つ以上ない場合は異常
    if (ps.size() < 2) {
      std::cout << "too few parameter" << std::endl;
      return false;
    }

    return true;
  }

  /**
   * @brief カッコの対応関係のペアを取得する関数
   * @details
   * checkConsistencyBracketsでtrueの時のみ使用すること。この関数でエラー処理はしていない。
   * @return vector<pair<int, int> >
   */
  std::vector<std::pair<int, int> > getConsistencyBracketsPair(
      const std::string& c) {
    std::stack<int> st;  // 左括弧の index を格納するスタック
    std::vector<std::pair<int, int> > ps;  // 対応を表すペア

    // ループを回す
    for (int i = 0; i < (int)c.size(); ++i) {
      if (c[i] == '(')
        st.push(i);
      else if (c[i] == ')') {
        int t = st.top();
        st.pop();
        ps.push_back({t, i});
      }
    }

    // 整合を出力
    sort(ps.begin(), ps.end());
#if _LAMBDA_DEBUG
    for (int i = 0; i < (int)ps.size(); ++i) {
      if (i) std::cout << ", ";
      std::cout << "(" << ps[i].first << ", " << ps[i].second << ")";
    }
    std::cout << std::endl;
#endif
    return ps;
  }
};