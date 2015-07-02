pathpwd=`pwd`
echo $pathpwd
matlab -nodisplay -nodesktop -r "cd('$pathpwd'); train('$pathpwd');"
