#Cabe Atwell Microbit WAV Sound File uploader  6/2019
import os, sys
from microfs import ls, rm, put, get, get_serial
#source_audio_filename="drum beat 0.wav"
target_audio_filename="output.raw" # output file name
# check if command line is correct
if len(sys.argv)!=2:
    print "Error in command line."
    if len(sys.argv)<2:
        print "No filename specified."
    else: 
        print "Too many arguments."
    print "usage: python file_uploader.py [source_wav_file_name]"
    exit()
else:
    source_audio_filename=sys.argv[1] # the second argument is the .wav file name to process
#source_audio_path="/home/pi/microbitwav/wav"
#print os.path.join(os.path.dirname(os.path.realpath(__file__)), "../wav/")
source_audio_path=os.path.join(os.path.dirname(os.path.realpath(__file__)), "../wav") # directory to look for the wav file
os.system("ffmpeg -y -i \""+source_audio_path+"/"+source_audio_filename+"\" -acodec pcm_u8 -f u8 -ac 1 -ar 7912 \""+source_audio_path+"/"+target_audio_filename+"\"") # convert wav to mono 8 bit

try:
    microbits_list=get_serial()  # check if micro:bit board is connected  
except:
    try:
        microbits_list
    except NameError:
        microbits_list = []

    if len(microbits_list)==0:
        print "No micro:bit board connected. Exiting."        

else:    
    Microbit_fileList = ls(serial=None)    
    # if files present - print file names, erase files
    if Microbit_fileList:		
        print "Files on the micro:bit board at the moment:"
        for filename in Microbit_fileList:
            print "\t"+filename
            
        print "Erasing files."
        for filename in Microbit_fileList:
            print "\t"+filename
            rm(filename, serial=None)
    else:
        print "No files on the micro:bit board at the moment."    
    
    # upload converted file to the micro:bit
    try:
        print "Uploading "+target_audio_filename
        put(source_audio_path+"/"+target_audio_filename, target=None, serial=None)
    except IOError:
        print "Upload failed"
    else:
        print "Uploaded: "+target_audio_filename
