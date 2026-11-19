# MBP (Modular Block/Brick Phone)

**WHAT MY PROJECT IS**

My project for Hack Club Fallen, is a modular phone prototype. Once I build it, it will be fully functional with a multitude of modules. It uses magnets and spring fingers/pins. You can use it as a normal phone most of the time, and when you want to change a piece of hardware, you simply pull a module on the back off and put a new one on, an example of this could be changing your battery, or using a wider lense camera, or switching from a magsafe charging port to a USB-C port.

**HOW TO USE IT**

You can use it as a normal phone most of the time, and when you want to change a piece of hardware, you simply pull a module on the back off and put a new one on, an example of this could be changing your battery, or using a wider lense camera, or switching from a magsafe charging port to a USB-C port.

**WHY I MADE IT**

I made this because I came across an idea from 2014 called 'phonebloks', it was a render of a phone that was essentially a breadboard with modules that attach to it. 
<img width="1280" height="1220" alt="image" src="https://github.com/user-attachments/assets/be482d45-cad6-4e2d-b58c-a4f9ea327bd0" />
Phonebloks - Dave Hakkens

My first idea was how cool this would be with magnets. THEN I found out about hack club FALLEN due to my friend Aromal messaging me. I love making hardware stuff and have made numerous things in the past which are similar-ish, such as a wide screen smart watch. So this is the project I chose And now im here, and I'm very happy with the prototype I've designed and cannot wait to be able to show it off in SHENZEN!

**SCREENSHOTS**

Full 3D assembly

<img width="820" height="684" alt="Screenshot from 2026-11-19 22-37-07" src="https://github.com/user-attachments/assets/f08dc713-2b33-4ca9-b3bb-0f055d04a006" />

<img width="800" height="621" alt="Screenshot from 2026-11-19 22-36-48" src="https://github.com/user-attachments/assets/1bcdc483-80cf-4ff9-870d-6f2c9f16e511" />

Exploded View

<img width="828" height="768" alt="Screenshot from 2026-11-19 23-06-38" src="https://github.com/user-attachments/assets/4e6914b7-2aab-4199-a846-544a5d472766" />

<img width="879" height="745" alt="Screenshot from 2026-11-19 23-05-37" src="https://github.com/user-attachments/assets/328eb392-5490-41a8-84ca-41e4b2305c8d" />




MAIN BOARD

SCHEMATIC

<img width="1123" height="654" alt="Screenshot from 2026-11-18 22-11-08" src="https://github.com/user-attachments/assets/a7a6ef86-8f73-4812-8b29-7b9e17b7a2fc" />

PCB

<img width="2160" height="4056" alt="Baseboard PCB" src="https://github.com/user-attachments/assets/05a017c4-3cd2-4040-80fe-4882b8909e66" />

<img width="1218" height="1193" alt="Screenshot from 2026-11-19 08-24-01" src="https://github.com/user-attachments/assets/356ad716-7f1d-4527-944d-6312be00955a" />

<img width="1366" height="1251" alt="Screenshot from 2026-11-19 08-24-24" src="https://github.com/user-attachments/assets/813dc3ef-ed64-4444-b39b-c56900cdbdd5" />




LAYOUT

I didn't want to crowd the read me, so it's best you go to the individual module folders to review the modules.

<img width="656" height="1297" alt="module_layout" src="https://github.com/user-attachments/assets/579285b4-102e-44f5-a92f-6fbb2b323c8d" />

MAIN MECHANISM

My project uses the unique connection method of magnets and spring pins. 4 Magnets are used per unit module, 3 of one polarity and 1 of the other so only 1 orientation is valid to avoid unwanted connections between modules and the base board. Modules carry the spring pins and have them soldered to them, these spring pins make contact to the base boards pads. This is why unfortunately even though I have read the design submission guidlines, I do have to use ENIG! as the HASL would quite quickly deteriorate and the layer beneath would oxidize and ruin the connection whereas gold will last much longer.

LAST BITS

 My project is quite large. I have segmented the files into a folder for each module, and one for the base board. Each of these folders contains an info.txt which tells you a bit about the part, and they also contain a .step of the entire module and images of the schematic + pcb, AND the gerber AND the .epro2 Easy EDA pro project file. These are things you should know:

- ONSHAPE link: https://cad.onshape.com/documents/f2b5af268e4416b960c7f24b/w/c8902db25726fdbc3c6632bf/e/53a77cd1040019ed3faeedc2?renderMode=0&uiState=6aff7a4689017861fb8b1852

- I am going to 3D print ALL the structural pieces at home, so CAD can and probably will be changed, for the absolute best margins so parts fit perfectly.

- Almost everything is epoxied together, I am using very thin epoxy which will attach everything you see in CAD.

- I have meticulously hand checked everything and used AI to cross reference with datasheets and check everything is okay by providing it with the netlist.

- My firmware was architecture by me but is written using AI tools such as Claude code. I really apologize for this, but I did not have time to write the firmware before I needed to submit my design and order the PCBs. I will be writing firmware for my modular phone as soon as PCB's are ordered and I have time.


- I understand my project is quite expensive, and I would be happy to pay for part of it, so if that is required, my messages are open to any updates.

- I'm sorry for using EasyEDA :( probably not your favorite to look at and have to review.

That's it! And thank you so much!!
