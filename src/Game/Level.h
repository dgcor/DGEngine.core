#pragma once

#include "LevelSurface.h"
#include "Save/SaveLevel.h"
#include "Shader.h"
#include "UIObject.h"

class Level : public UIObject
{
private:
	LevelSurface surface;
	GameShader* gameShader{ nullptr };

	std::string id;
	std::string name;

	bool pause{ false };
	bool hasMouseInside{ false };

	friend void Save::save(const std::string_view filePath,
		const Save::Properties& props, const Game& game, const Level& level);
	friend void Save::serialize(void* serializeObj,
		const Save::Properties& props, const Game& game, const Level& level);

public:
	void Init(Game& game);

	void setShader(GameShader* shader) noexcept { gameShader = shader; }

	void Id(const std::string_view id_) { id = id_; }
	void Name(const std::string_view name_) { name = name_; }

	std::shared_ptr<Action> getAction(uint16_t nameHash16) const noexcept override;
	bool setAction(uint16_t nameHash16, const std::shared_ptr<Action>& action) noexcept override;

	Anchor getAnchor() const noexcept override { return surface.getAnchor(); }
	void setAnchor(const Anchor anchor) noexcept override { surface.setAnchor(anchor); }

	void updateSize(const Game& game) override { surface.updateSize(game); }

	const sf::Vector2f& DrawPosition() const noexcept override { return surface.Position(); }
	const sf::Vector2f& Position() const noexcept override { return surface.Position(); }
	void Position(const sf::Vector2f& position) override { surface.Position(position); }
	sf::Vector2f Size() const noexcept override { return surface.Size(); }
	void Size(const sf::Vector2f& size) override { surface.Size(size); }

	bool Pause() const noexcept { return pause; }
	void Pause(bool pause_) noexcept { pause = pause_; }

	bool Visible() const noexcept override { return surface.visible; }
	void Visible(bool visible) noexcept override { surface.visible = visible; }

	void save(const std::string_view filePath,
		const Save::Properties& props, const Game& game) const
	{
		Save::save(filePath, props, game, *this);
	}
	void serialize(void* serializeObj, const Save::Properties& props,
		const Game& game, const Level& level)
	{
		Save::serialize(serializeObj, props, game, *this);
	}

	void draw(const Game& game, sf::RenderTarget& target) const override;
	void update(Game& game) override;
	bool getProperty(const std::string_view prop, Variable& var) const override;
	const Queryable* getQueryable(const std::string_view prop) const override;

	std::vector<std::variant<const Queryable*, Variable>> getQueryableList(
		const std::string_view prop) const;
};
