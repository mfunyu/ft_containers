#ifndef MAP_HPP
#define MAP_HPP

namespace ft {

template <class Key, class T, class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T> > >
class map
{
  private:
  public:
	map();
	~map();
	map(map const& other);
	map& operator=(map const& other);
};

} // namespace ft

#endif /* MAP_HPP */
