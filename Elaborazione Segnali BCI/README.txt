Nel file zip sono presenti le seguenti cartelle
  MATLAB
    BCI: contiene gli script relativi all'analisi dei segnali
    Funzioni: contiene le funzioni utilizzate negli script
    
Importazione segnali txt:
  1) Aprire il file e copiare tutto il contenuto
  2) Eseguire script SignalImport
  
Elaborazione segnali importati:
  1) gli script vanno eseguiti in questo ordine:
    1.1) SignalParameters
    1.2) SignalFilter
    1.3) SignalAnalysis
    Nota: lo script SignalProcess esegue questi 3 script in ordine
  2) i risultati possono essere plottati con
    - SignalPlotSamples: esegue il plot dei campioni
    - SignalPlotSpectrum: esegue il plot dello spettro
    - SignalPlotAll: esegue contemporaneamente il plot dei campioni e dello spettro
    Nota: Gli script mettono in pausa MatLab. Premere un qualsiasi tasto per procedere
          Per interrompere l'esecuzione degli script premere <Ctrl + c>
  
  