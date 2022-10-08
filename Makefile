run:
	mv Assignment-2/include/boost ../
	cp -r Assignment-2 HW2_MCS212138
	zip -r HW2_MCS212138.zip HW2_MCS212138 
	git add -A
	git commit -m "zip changed"
	git push origin main
	mv ../boost Assignment-2/include/
clean:
	rm -rf  HW2_MCS212138 HW2_MCS212138.zip
