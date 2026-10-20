#include<iostream>
#include<vector>

using segment = std::pair<int, int>; 

bool is_intersect(segment& s1, segment& s2)
{
	return (s1.second >= s2.first || s2.second >= s1.first);
}

void merge_seg(segment& s1, segment& s2)
{
	s1.second = s2.second;
}

int main()
{
	std::vector<std::pair<int, int>> segments;

	auto cmp = [](segment& s1, segment& s2) {return s1.first < s2.first; };
	
	std::sort(segments.begin(), segments.end(), cmp);

	int iterator = 0
	segment tmp = segments.front();
	while (iterator < segments.size())
	{
		if(is_intersect(tmp, iterator))
		{
			merge_seg(tmp, segments[iterator]);
		}
		else
		{
			std::cout << tmp.s1 << " " << tmp.s2 << '\n';
			tmp = segments[iterator];
		}
		iterator++;
	}
}