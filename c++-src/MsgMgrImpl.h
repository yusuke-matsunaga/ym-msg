﻿#ifndef MSGMGRIMPL_H
#define MSGMGRIMPL_H

/// @file MsgMgrImpl.h
/// @brief MsgHandler のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2019 Yusuke Matsunaga
/// All rights reserved.


#include "ym/MsgHandler.h"


BEGIN_NAMESPACE_YM

//////////////////////////////////////////////////////////////////////
/// @class MsgMgrImpl MsgMgrImpl.h "MsgMgrImpl.h"
/// @brief MsgMgr の実際の処理を行うクラス
//////////////////////////////////////////////////////////////////////
class MsgMgrImpl
{
public:

  /// @brief コンストラクタ
  MsgMgrImpl();

  /// @brief デストラクタ
  ~MsgMgrImpl();


public:
  //////////////////////////////////////////////////////////////////////
  // ハンドラの登録
  //////////////////////////////////////////////////////////////////////

  /// @brief ハンドラを登録する．
  /// @param[in] handler 登録するハンドラ
  void
  reg_handler(MsgHandler* handler);

  /// @brief ハンドラの登録を解除する．
  /// @param[in] handler 解除するハンドラ
  void
  unreg_handler(MsgHandler* handler);

  /// @brief すべてのハンドラの登録を解除する．
  void
  unreg_all_handlers();


public:
  //////////////////////////////////////////////////////////////////////
  // メッセージの出力
  //////////////////////////////////////////////////////////////////////

  /// @brief メッセージを出力する．
  /// @param[in] src_file この関数を読んでいるソースファイル名
  /// @param[in] src_line この関数を読んでいるソースの行番号
  /// @param[in] type メッセージの種類
  /// @param[in] label メッセージラベル
  /// @param[in] msg メッセージ本文
  void
  put_msg(const char* src_file,
	  int src_line,
	  MsgType type,
	  const char* label,
	  const char* msg);


public:
  //////////////////////////////////////////////////////////////////////
  // 統計情報の管理
  //////////////////////////////////////////////////////////////////////

  /// @brief カウント値をクリアする．
  void
  clear_count();

  /// @brief 全メッセージ数を得る．
  int
  msg_num() const;

  /// @brief エラーメッセージ数を得る．
  int
  error_num() const;

  /// @brief 警告メッセージ数を得る．
  int
  warning_num() const;

  /// @brief 情報メッセージ数を得る．
  int
  info_num() const;

  /// @brief 失敗メッセージ数を得る．
  int
  fail_num() const;

  /// @brief デバッグメッセージ数を得る．
  int
  debug_num() const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // ハンドラのリスト
  list<MsgHandler*> mHandlerList;

  // エラーメッセージ数
  int mErrorNum;

  // 警告メッセージ数
  int mWarningNum;

  // 情報メッセージ数
  int mInfoNum;

  // 失敗メッセージ数
  int mFailNum;

  // デバッグメッセージ数
  int mDebugNum;

};

END_NAMESPACE_YM

#endif // MSGMGRIMPL_H
