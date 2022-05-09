#!/bin/bash

# --------------------------------- color def -------------------------------- #
THICK="\033[1m"
CYAN="\033[1;36m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
RESET="\033[m"
PROMPT="${CYAN}$>${RESET} "
INFO=$CYAN
KO="${THICK}[ ${RED}KO${RESET} ${THICK}]"
OK="${THICK}[ ${GREEN}OK${RESET} ${THICK}]"
EOL="\n${RESET}"

# ----------------------------------- setup ---------------------------------- #
rm ft_review std_review ft std

printf "${PROMPT}make review${EOL}"
make review

# --------------------------------- run test --------------------------------- #
printf "${PROMPT}./std_review > std${EOL}"
./std_review > std

printf "${PROMPT}./ft_review > ft${EOL}"
./ft_review > ft 

printf "${PROMPT}diff std ft${EOL}"
diff std ft

if [ $? == 1 ] ; then
	printf "${KO} : diff found${EOL}"
else 
	printf "${OK} : no diff found${EOL}"
fi

printf "${PROMPT}cat ft # executed result${EOL}"
cat ft

# --------------------------------- clean up --------------------------------- #
rm ft_review std_review
