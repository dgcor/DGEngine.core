#include "Level.h"
#include "Game.h"
#include "Utils/Utils.h"

void Level::Init(Game& game)
{
	surface.init(game);
	surface.updateView(game);
}

std::shared_ptr<Action> Level::getAction(uint16_t nameHash16) const noexcept
{
	return nullptr;
}

bool Level::setAction(uint16_t nameHash16, const std::shared_ptr<Action>& action) noexcept
{
	return false;
}

void Level::draw(const Game& game, sf::RenderTarget& target) const
{
	if (Visible() == false)
	{
		return;
	}

	auto origView = target.getView();

	surface.clear(sf::Color::Transparent);

	auto surfaceStates(sf::RenderStates::Default);
	if (gameShader != nullptr)
	{
		auto shader = gameShader->shader.get();
		surfaceStates.shader = shader;
		for (auto uniformHash : gameShader->uniforms)
		{
			switch (uniformHash)
			{
			case str2int16("elapsedTime"):
			{
				shader->setUniform("elapsedTime", game.getTotalElapsedTime().asSeconds());
				break;
			}
			case str2int16("mousePosition"):
			{
				if (hasMouseInside == true)
				{
					shader->setUniform("mousePosition", sf::Glsl::Vec2(
						(game.MousePositionf().x - surface.Position().x) /
						surface.Size().x,
						(game.MousePositionf().y - surface.Position().y) /
						surface.Size().y
					));
				}
				break;
			}
			case str2int16("textureSize"):
			{
				shader->setUniform("textureSize", sf::Glsl::Vec2(
					surface.Size().x,
					surface.Size().y
				));
				break;
			}
			case str2int16("visibleRect"):
			{
				shader->setUniform("visibleRect", sf::Glsl::Vec4(
					surface.visibleRect.left,
					surface.visibleRect.top,
					surface.visibleRect.width,
					surface.visibleRect.height
				));
				break;
			}
			default:
				break;
			}
		}
	}
	surface.draw(target, surfaceStates);

	target.setView(origView);
}

void Level::update(Game& game)
{
	if (Visible() == false)
	{
		return;
	}
	if (pause == true)
	{
		return;
	}

	sf::FloatRect rect(surface.Position(), surface.Size());
	if (rect.contains(game.MousePositionf()) == true)
	{
		hasMouseInside = true;
	}
	else
	{
		hasMouseInside = false;
	}
}

bool Level::getProperty(const std::string_view prop, Variable& var) const
{
	if (prop.size() <= 1)
	{
		return false;
	}
	auto props = Utils::splitStringIn2(prop, '.');
	auto propHash = str2int16(props.first);
	switch (propHash)
	{
	case str2int16("id"):
		var = Variable(id);
		return true;
	case str2int16("name"):
		var = Variable(name);
		return true;
	default:
		return getUIObjProp(propHash, props.second, var);
	}
	return false;
}

const Queryable* Level::getQueryable(const std::string_view prop) const
{
	if (prop.empty() == true)
	{
		return this;
	}
	return nullptr;
}

std::vector<std::variant<const Queryable*, Variable>> Level::getQueryableList(
	const std::string_view prop) const
{
	return {};
}
