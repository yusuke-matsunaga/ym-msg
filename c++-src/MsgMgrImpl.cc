
/// @file MsgMgrImpl.cc
/// @brief MsgMgrImpl の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2019 Yusuke Matsunaga
/// All rights reserved.


#include "MsgMgrImpl.h"


BEGIN_NAMESPACE_YM

//////////////////////////////////////////////////////////////////////
// MsgMgrImpl
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
MsgMgrImpl::MsgMgrImpl()
{
  clear_count();
}

// @brief デストラクタ
// @note ここに登録してあるすべてのハンドラは削除される．
MsgMgrImpl::~MsgMgrImpl()
{
  unreg_all_handlers();
}

// @brief ハンドラを登録する．
// @param[in] handler 登録するハンドラ
void
MsgMgrImpl::reg_handler(MsgHandler* handler)
{
  ASSERT_COND( handler->mMgr == nullptr );
  handler->mMgr = this;
  mHandlerList.push_back(handler);
  handler->mIter = -- mHandlerList.end();
}

// @brief ハンドラの登録を解除する．
// @param[in] handler 解除するハンドラ
void
MsgMgrImpl::unreg_handler(MsgHandler* handler)
{
  ASSERT_COND( handler->mMgr == this );
  mHandlerList.erase(handler->mIter);
  handler->mMgr = nullptr;
}

// @brief すべてのハンドラの登録を解除する．
void
MsgMgrImpl::unreg_all_handlers()
{
  for ( auto handler: mHandlerList ) {
    handler->mMgr = nullptr;
  }
  mHandlerList.clear();
}

// @brief メッセージを出力する．
// @param[in] src_file この関数を読んでいるソースファイル名
// @param[in] src_line この関数を読んでいるソースの行番号
// @param[in] file_loc ファイル位置
// @param[in] type メッセージの種類
// @param[in] label メッセージラベル
// @param[in] body メッセージ本文
void
MsgMgrImpl::put_msg(const char* src_file,
		    int src_line,
		    MsgType type,
		    const char* label,
		    const char* msg)
{
  switch ( type ) {
  case MsgType::Error:    ++ mErrorNum; break;
  case MsgType::Warning:  ++ mWarningNum; break;
  case MsgType::Info:     ++ mInfoNum; break;
  case MsgType::Failure:  ++ mFailNum; break;
  case MsgType::Debug:    ++ mDebugNum; break;
  default: ASSERT_NOT_REACHED;
  }

  for ( auto handler: mHandlerList ) {
    handler->event_proc(src_file, src_line, type, label, msg);
  }
}

// @brief カウント値をクリアする．
void
MsgMgrImpl::clear_count()
{
  mErrorNum = 0;
  mWarningNum = 0;
  mInfoNum = 0;
  mFailNum = 0;
  mDebugNum = 0;
}

// @brief 全メッセージ数を得る．
int
MsgMgrImpl::msg_num() const
{
  return mErrorNum + mWarningNum + mInfoNum + mFailNum + mDebugNum;
}

// @brief エラーメッセージ数を得る．
int
MsgMgrImpl::error_num() const
{
  return mErrorNum;
}

// @brief 警告メッセージ数を得る．
int
MsgMgrImpl::warning_num() const
{
  return mWarningNum;
}

// @brief 情報メッセージ数を得る．
int
MsgMgrImpl::info_num() const
{
  return mInfoNum;
}

// @brief 失敗メッセージ数を得る．
int
MsgMgrImpl::fail_num() const
{
  return mFailNum;
}

// @brief デバッグメッセージ数を得る．
int
MsgMgrImpl::debug_num() const
{
  return mDebugNum;
}

END_NAMESPACE_YM
