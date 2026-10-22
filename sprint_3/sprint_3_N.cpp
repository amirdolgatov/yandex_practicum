#include<iostream>
#include<vector>
#include<algorithm>

using segment = std::pair<int, int>; 

bool is_intersect(segment& s1, segment& s2)
{
	if (s1.first <= s2.first)
	{
		return (s1.second >= s2.first);
	}
	else
	{
		return (s2.second >= s1.first);
	}
}

// merge to current
void merge_seg(segment& s1, segment& s2)
{
	s1.first = std::min(s1.first, s2.first);
	s1.second = std::max(s1.second, s2.second);
}

int main()
{
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<segment> segments(n);
    for (auto& s : segments)
    {
        std::cin >> s.first >> s.second;
    }

	auto cmp = [](segment& s1, segment& s2) 
	{return s1.first < s2.first; };
	
	std::sort(segments.begin(), segments.end(), cmp);

	segment tmp = segments.front();
	for (int iterator = 0; iterator < segments.size(); ++iterator)
	{
		if(is_intersect(tmp, segments[iterator]))
		{
			merge_seg(tmp, segments[iterator]);
		}
		else
		{
			std::cout << tmp.first << " " << tmp.second << '\n';
			tmp = segments[iterator];
		}
	}

	std::cout << tmp.first << " " << tmp.second << '\n';

	// как вывести оставшийся промежуток?
	// 
}