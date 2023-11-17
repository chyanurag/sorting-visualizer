#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;

std::vector<std::vector<int>> bubbleSort(std::vector<int>& v){
	std::vector<std::vector<int>> result;
	for(int i = 0; i < v.size() - 1; i++){
		for(int j = 0; j < v.size() - i - 1; j++){
			if(v[j+1] < v[j]){
				int temp = v[j];
				v[j] = v[j+1];
				v[j+1] = temp;
			}
		}
		result.push_back(v);
	}
	return result;
}

void draw_bars(std::vector<int> bars, RenderWindow& window){
	float max = 0.f;
	for(float f : bars){
		if(f > max){
			max = f;
		}
	}
	const float BAR_HEIGHT = window.getSize().y/max;
	const float BAR_WIDTH = window.getSize().x/(bars.size());
	for(int i = 0; i < bars.size(); i++){
		RectangleShape bar(Vector2f(BAR_WIDTH, bars[i]*BAR_HEIGHT));
		bar.setFillColor(Color::Green);
		bar.setOutlineColor(Color::Red);
		bar.setOutlineThickness(5.f);
		bar.setPosition(i*(BAR_WIDTH+10.f), (max-bars[i])*BAR_HEIGHT);
		window.draw(bar);
	}
}

int main(){
	RenderWindow window(VideoMode(1920, 1080), "Game", Style::Fullscreen);
	Clock clock;
	int start = clock.getElapsedTime().asSeconds();
	int idx = 0;
	std::vector<int> v = {3, 4, 1, 5, 2, 7, 9};
	auto result = bubbleSort(v);
	while(window.isOpen()){
		Event ev;
		while(window.pollEvent(ev)){
			switch(ev.type){
				case Event::Closed:
					window.close();
					break;
			}
		}
		window.clear();
		if(clock.getElapsedTime().asSeconds() - start > 1.f){
			start = clock.getElapsedTime().asSeconds();
			if(idx < result.size() - 1){
				idx++;
			}
		}
		draw_bars(result[idx], window);
		window.display();
	}
	return 0;
}
