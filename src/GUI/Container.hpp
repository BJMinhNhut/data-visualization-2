//
// Created by MINH NHUT on 7/2/2023.
//

#ifndef DATAVISUALIZATION2_CONTAINER_HPP
#define DATAVISUALIZATION2_CONTAINER_HPP

#include <GUI/Component.hpp>

#include <memory>
#include <vector>

namespace GUI {
    class Container : public Component {
    public:
        typedef std::shared_ptr<Container> Ptr;

    public:
        Container();

	 void pack(const Component::Ptr& component);

	    void activateChild(const Component::Ptr& component);

	    void reset();

	    bool isSelectable() const override;

	    bool update(sf::Time dt) override;

	    bool handleEvent(const sf::Event& event) override;

	    bool contains(sf::Vector2i point) const override;

	    void deselect() override;

	   private:
	    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	    bool hasSelection() const;

        bool hasActivation() const;

        void select(std::size_t index);

        void activate(std::size_t index);

	    void updateSelect(sf::Vector2i point);

	   private:
        std::vector<Component::Ptr> mChildren;
        int mSelectedChild;
        int mActivatedChild;
    };
}  // namespace GUI

#endif //DATAVISUALIZATION2_CONTAINER_HPP
