# Tropicos download instructions

1. Notify Tropicos admin that you will be running the download. This is an important courtesy as this operation places a heavy load on the server for several days. Suggest contact Chuck Miller: `Chuck.Miller@mobot.org`
2. Obtain API key if you don't already have one. Chuck Miller is best contact. See above.
3. Add API key parameter to file. Should be around line 25:

    ```
    Readonly::Scalar my $key => '<API_KEY>'
    ```

4. Run the download script in unix screen: 

    ```
    screen
    perl retrieve_from_mbg_api.pl 
    ```
    
    Will take about 3 days to run. Results will be in same directory as the script.