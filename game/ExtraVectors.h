#pragma once
namespace ExtraVectors {
	template<typename T> // method for finding a specific member in a vector
	static T find(vector<T> const & vec, T element) { 
		for (int i = 0; i < vec.size(); i++) {
			if (vec.at(i) == element) return vec.at(i);
		}
		return 0;
	}
} 