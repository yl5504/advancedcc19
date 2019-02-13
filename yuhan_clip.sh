#Yuhan's 40 second -- happiness

#trim the needed part from existing videos
ffmpeg -i 1.mp4 -ss 00:27 -to 00:37 -c:v copy -c:a copy a.mp4

ffmpeg -i 2.mp4 -ss 04:40 -to 04:50 -c:v copy -c:a copy b.mp4

ffmpeg -i 3.mp4 -ss 03:20 -to 03:20 -c:v copy -c:a copy c.mp4

ffmpeg -i 4.mp4 -ss 00:15 -to 00:25 -c:v copy -c:a copy 4_output.mp4

ffmpeg -i 4_output.mp4 -vf hflip -c:a copy d.mp4

#use a series a picture to create a video
ffmpeg -start_number 000000060 -i 'defaultCanvas-%9d.png' -c:v libx264 -pix_fmt yuv420p image.mp4
#slow down
ffmpeg -i image.mp4 -filter:v "setpts=2.0*PTS" e.mp4

ffmpeg -i 3.mp4 -ss 01:12 -to 01:18 -c:v copy -c:a copy f.mp4

#combine the videos together
$ cat mylist.txt
file 'a.mp4'
file 'b.mp4'
file 'c.mp4'
file 'd.mp4'
file 'e.mp4'
file 'f.mp4'

ffmpeg -f concat -i mylist.txt -c copy output.mp4

ffmpeg -i output.mp4 -i happiness.mp3 -c copy -map 0:v:0 -map 1:a:0 yuhan_clip.mp4

#transfer to MTS
ffmpeg -i yuhan_clip.mp4 -q 0 yuhan_clip.MTS
