#pragma once

#include "Action.h"
#include "Animation.h"
#include "Game.h"

class ActAnimationPause : public Action
{
private:
	std::string id;
	bool pause;
	bool reset;

public:
	ActAnimationPause(const std::string_view id_, bool pause_, bool reset_)
		: id(id_), pause(pause_), reset(reset_) {}

	bool execute(Game& game) override
	{
		auto animation = game.Resources().getDrawable<Animation>(id);
		if (animation != nullptr)
		{
			animation->Pause(pause);
			if (reset == true)
			{
				animation->reset();
				animation->updateTexture();
			}
		}
		return true;
	}
};

class ActAnimationSetAnimation : public Action
{
private:
	std::string id;
	std::string idTexturePack;
	int32_t groupIdx;
	int32_t directionIdx;
	sf::Time refresh;
	bool resetAnimation;
	bool updateAnimationType;
	bool setCompositeTexture;

public:
	ActAnimationSetAnimation(const std::string_view id_,
		const std::string_view idTexturePack_, int32_t groupIdx_, int32_t directionIdx_,
		sf::Time refresh_, bool resetAnimation_, bool updateAnimationType_,
		bool setCompositeTexture_) : id(id_), idTexturePack(idTexturePack_),
		groupIdx(groupIdx_), directionIdx(directionIdx_), refresh(refresh_),
		resetAnimation(resetAnimation_), updateAnimationType(updateAnimationType_),
		setCompositeTexture(setCompositeTexture_) {}

	bool execute(Game& game) override
	{
		auto animation = game.Resources().getDrawable<Animation>(id);
		if (animation != nullptr)
		{
			TexturePackVariant texVar;
			if (idTexturePack.empty() == false)
			{
				if (setCompositeTexture == false)
				{
					auto tex = game.Resources().getTexturePack(idTexturePack);
					if (tex != nullptr)
					{
						texVar = std::move(tex);
					}
				}
				else
				{
					auto tex = game.Resources().getCompositeTexture(idTexturePack);
					if (tex != nullptr)
					{
						texVar = std::move(tex);
					}
				}
			}
			if (texVar.holdsNullTexturePack() == false)
			{
				animation->setAnimation(
					std::move(texVar), groupIdx, directionIdx,
					resetAnimation, updateAnimationType
				);
			}
			else
			{
				animation->setAnimation(
					groupIdx, directionIdx,
					resetAnimation, updateAnimationType
				);
			}
			if (refresh.asMicroseconds() > 0)
			{
				animation->setFrameTime(refresh);
			}
		}
		return true;
	}
};

class ActAnimationSetRefresh : public Action
{
private:
	std::string id;
	sf::Time refresh;

public:
	ActAnimationSetRefresh(const std::string_view id_, sf::Time refresh_)
		: id(id_), refresh(refresh_) {}

	bool execute(Game& game) override
	{
		if (refresh.asMicroseconds() > 0)
		{
			auto animation = game.Resources().getDrawable<Animation>(id);
			if (animation != nullptr)
			{
				animation->setFrameTime(refresh);
			}
		}
		return true;
	}
};
