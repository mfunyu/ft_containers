#!/bin/bash

# --------------------------------- color def -------------------------------- #
THICK="\033[1m"
CYAN="\033[1;36m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
RESET="\033[m"
PROMPT="${CYAN}$>${RESET}"
INFO=$CYAN
ERROR="${THICK}[ ${RED}ERROR${RESET} ${THICK}]"
OK="${THICK}[ ${GREEN}OK${RESET} ${THICK}]"
EOL="\n${RESET}"

# --------------------------------- settings --------------------------------- #
logfile="result.log"
stdfile="std.log"

# ------------------------------- check tester ------------------------------- #
printf "${INFO}Checking for Tester Validity ...${EOL}"
printf "${PROMPT} make -s std${EOL}"
make -s std > /dev/null

printf "${PROMPT} ./std_test > $stdfile${EOL}"
./std_test > $stdfile
if [ $? == 1 ] ; then
	cat $stdfile
	printf "\n"
	printf "${ERROR} : Tester does not return 100%% for STD${EOL}"
	exit
fi
printf "${OK} : Tester returns 100%% for STD${EOL}"

printf "\n"

# --------------------------------- run test --------------------------------- #
printf "${INFO}Runnning Tester ...${EOL}"
printf "${PROMPT} make -s ft${EOL}"
make -s ft > /dev/null

./run_test 2>> $logfile
printf "See ./$logfile for more details ...${EOL}"


rm $stdfile
