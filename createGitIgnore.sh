echo "Checking for existing gitignore"
if [ -f ".gitignore" ]
then
	echo "Removing existing gitignore"
	rm .gitignore
fi

echo "Adding compiled files"
echo "# Compiled Files" >> .gitignore
pwd | sed "s:.*/::" >> .gitignore
pwd | sed "s:.*/::" | sed "s:.*.:&_debug:" >> .gitignore

echo "Adding object files"
printf "\n# Object Files\n" >> .gitignore
echo "obj" >> .gitignore

echo "Adding libraries"
printf "\n# Libraries\n" >> .gitignore
echo "bin/libs" >> .gitignore
