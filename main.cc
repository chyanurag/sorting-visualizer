#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;

std::vector<std::vector<int>> selectionSort(std::vector<int>& v){
	std::vector<std::vector<int>> result;
	for(int i = 0; i < v.size(); i++){
		int curr = v[i];
		int idx = i; 
        for(int j = i + 1; j < v.size(); j++){
			if(v[j] < v[idx]){
				idx = j;
			}
		}
		v[i] = v[idx];
		v[idx] = curr;
		result.push_back(v);
	}
	return result;
}

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
		bar.setFillColor(Color::White);
		bar.setPosition(i*BAR_WIDTH, (max-bars[i])*BAR_HEIGHT);
		window.draw(bar);
	}
}

int main(){
	RenderWindow window(VideoMode(1920, 1080), "Sorting Visualiser", sf::Style::Fullscreen);
	Clock clock;
	float prev = clock.getElapsedTime().asSeconds();
	int idx = 0;
	std::vector<int> v;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    int barNums = 200;
	for(int i = 1; i <= barNums; i++){
		v.push_back(i);
	}
	std::shuffle(v.begin(), v.end(), std::default_random_engine(seed));
	auto result = selectionSort(v);
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
        float curr = clock.getElapsedTime().asSeconds();
		if(curr - prev >= .01f){
			prev = curr;
			if(idx < result.size() - 1){
				idx++;
			}
        }
		draw_bars(result[idx], window);
		window.display();
	}
	return 0;
}
