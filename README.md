# ft_containers
lv5 project @42Tokyo 

[![mfunyu's 42 ft_containers Score](https://badge42.vercel.app/api/v2/cl39q9bth003509lhnivqm9hg/project/2517118)](https://github.com/JaeSeoKim/badge42)
### Notion
- [ft_containers log >>>](https://quilled-discovery-253.notion.site/ft_containers-Reviewee-666ab8f6016e4f5aa21edb46b9b87b24)

# Project Overview

Recreate containers from C++ STL(Standard Template Library) in C++98

Files are under `./includes` directory

### Containers
| Containers                                                   | Iterator                | Inner Tree     | 
| :----------------------------------------------------------- | :---------------------: | :------------: |
| [vector](https://en.cppreference.com/w/cpp/container/vector) | random_access_iterator  | N/A            |
| [map](https://en.cppreference.com/w/cpp/container/map)       | Red-Black tree iterator | Red-Black tree |
| [stack](https://en.cppreference.com/w/cpp/container/stack)   | N/A                     | N/A            | 
| [set](https://en.cppreference.com/w/cpp/container/set)       | Red-Black tree iterator | Red-Black tree |

### Others

| category  | functions | 
|  :---:    | :---      |
| Iterators | • [iterators_traits](https://en.cppreference.com/w/cpp/iterator/iterator_traits)      <br>• [reverse_iterator](https://en.cppreference.com/w/cpp/iterator/reverse_iterator) | 
| Types     | • [enable_if](https://en.cppreference.com/w/cpp/types/enable_if) (in a C++98 manner)  <br>• [is_integral](https://en.cppreference.com/w/cpp/types/is_integral)
| Algorithm | • [equal](https://en.cppreference.com/w/cpp/algorithm/equal)                          <br>• [lexicographical_compare](https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare)
| Utilities | • [pair](https://en.cppreference.com/w/cpp/utility/pair)                              <br>• [make_pair](https://en.cppreference.com/w/cpp/utility/pair/make_pair)

# Red-Black tree
- Display using `tree` command
- Create directories strutrue as tree
- Setting color by setting `LS_COLORS`
  ```bash
  LS_COLORS="di=00;91:ow=30;107"
  ```
  - Setting different permission depending on node's color
    ```
    setting different permission
    if black : 0777
    if red   : 0755
    ```
- Display Example

  <img width="236" alt="SS 2022-05-18 13 10 13 1" src="https://user-images.githubusercontent.com/60470877/168955812-db7b97f4-2119-41a6-b5ae-a9000d87b1c2.png">

