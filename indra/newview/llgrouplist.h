/** 
 * @file llgrouplist.h
 * @brief List of the groups the agent belongs to.
 *
 * $LicenseInfo:firstyear=2009&license=viewergpl$
 * 
 * Copyright (c) 2009, Linden Research, Inc.
 * 
 * Second Life Viewer Source Code
 * The source code in this file ("Source Code") is provided by Linden Lab
 * to you under the terms of the GNU General Public License, version 2.0
 * ("GPL"), unless you have obtained a separate licensing agreement
 * ("Other License"), formally executed by you and Linden Lab.  Terms of
 * the GPL can be found in doc/GPL-license.txt in this distribution, or
 * online at http://secondlifegrid.net/programs/open_source/licensing/gplv2
 * 
 * There are special exceptions to the terms and conditions of the GPL as
 * it is applied to this Source Code. View the full text of the exception
 * in the file doc/FLOSS-exception.txt in this software distribution, or
 * online at
 * http://secondlifegrid.net/programs/open_source/licensing/flossexception
 * 
 * By copying, modifying or distributing this software, you acknowledge
 * that you have read and understood your obligations described above,
 * and agree to abide by those obligations.
 * 
 * ALL LINDEN LAB SOURCE CODE IS PROVIDED "AS IS." LINDEN LAB MAKES NO
 * WARRANTIES, EXPRESS, IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY,
 * COMPLETENESS OR PERFORMANCE.
 * $/LicenseInfo$
 */

#ifndef LL_LLGROUPLIST_H
#define LL_LLGROUPLIST_H

#include "llflatlistview.h"
#include "llpanel.h"

class LLGroupList: public LLFlatListView
{
	LOG_CLASS(LLGroupList);
public:
	struct Params : public LLInitParam::Block<Params, LLFlatListView::Params> 
	{
		Params();
	};

	LLGroupList(const Params& p);
	BOOL update(const std::string& name_filter = LLStringUtil::null);
	void toggleIcons();
	bool getIconsVisible() const { return mShowIcons; }

private:
	void addNewItem(const LLUUID& id, const std::string& name, const LLUUID& icon_id, BOOL is_bold, EAddPosition pos = ADD_BOTTOM);

	bool mShowIcons;
};

class LLButton;
class LLIconCtrl;
class LLTextBox;

class LLGroupListItem : public LLPanel
{
public:
	LLGroupListItem();
	/*virtual*/ BOOL postBuild();
	/*virtual*/ void setValue(const LLSD& value);
	void onMouseEnter(S32 x, S32 y, MASK mask);
	void onMouseLeave(S32 x, S32 y, MASK mask);

	const LLUUID& getGroupID() const			{ return mGroupID; }
	const std::string& getGroupName() const		{ return mGroupName; }

	void setName(const std::string& name);
	void setGroupID(const LLUUID& group_id);
	void setGroupIconID(const LLUUID& group_icon_id);
	void setGroupIconVisible(bool visible);

private:
	void setActive(bool active);
	void onInfoBtnClick();

	LLTextBox*	mGroupNameBox;
	LLUUID		mGroupID;
	LLIconCtrl* mGroupIcon;
	LLButton*	mInfoBtn;

	std::string	mGroupName;

	static S32	sIconWidth; // icon width + padding
};
#endif // LL_LLGROUPLIST_H
