run:
	cp -r Assignment-2 HW2_MCS212138 
	zip -r HW2_MCS212138.zip HW2_MCS212138 
	rm -rf HW2_MCS212138
	git add -A
	git commit -m "zip changed"
	git push origin main
clean:
	rm -rf HW2_MCS212138.zip
