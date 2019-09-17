# LinearStaplerInstrumentation
## Steps
1. Branch the repository
2. Clone your branch
3. Open LSI.sln
4. Ensure Solution Configuration is 'Debug' and Solution Platform is 'x64'
5. Check that the NI folders are in Properties --> C/C++ --> Additional Include Directories (Something like 'C:\Program Files (x86)\National Instruments\Shared\ExternalCompilerSupport\C\include') and Properties --> Linker --> Additional Library Directories (Some like 'C:\Program Files (x86)\National Instruments\Shared\ExternalCompilerSupport\C\lib64\msvc')
6. Include the NI Library 'NIDAQmx.lib' under Properties --> Linker --> Input --> Additional Dependencies
7, Ensure the NI DAQ is plugged into a USB port.
