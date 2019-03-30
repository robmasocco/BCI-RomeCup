% ===== 3D plot =====
if plotGraphics <= 0
    figure(3);

    ax_sx = subplot(1,2,1);
    title('Spectrum SX 3D');
    hold on;
    for i = start_fft:final_fft  
        time = ((i - 1) * step_t + sec) * ones(1, N/2);
        if plotSignals <= 0
            plot3(f, time, S_sx(i,:), 'Color', [0 0.4470 0.7410]);
        end
        if plotSignals >= 0
            plot3(f, time, S_f_sx(i,:), 'Color', [0.8500 0.3250 0.0980]); 
        end
    end
    if plotSignals == 0
        legend("Segnale originale", "Segnale filtrato");
    elseif plotSignals <= -1
        legend("Segnale originale");
    elseif plotSignals >= 1
        legend("Segnale filtrato");
    end
    xlabel('Frequency (hz)');
    ylabel('Time (s)');
    zlabel('Magnitude');
    axis([f1 f2 start_fft*step_t final_fft*step_t 0 a]);
    view([0,-1,0]);
    grid on;

    ax_dx = subplot(1,2,2);
    title('Spectrum DX 3D');
    hold on;
    for i = start_fft:final_fft  
        time = ((i - 1) * step_t + sec) * ones(1, N/2);
        if plotSignals <= 0
            plot3(f, time, S_dx(i,:), 'Color', [0 0.4470 0.7410]);
        end
        if plotSignals >= 0
            plot3(f, time, S_f_dx(i,:), 'Color', [0.8500 0.3250 0.0980]);
        end
    end
    if plotSignals == 0
        legend("Segnale originale", "Segnale filtrato");
    elseif plotSignals <= -1
        legend("Segnale originale");
    elseif plotSignals >= 1
        legend("Segnale filtrato");
    end
    xlabel('Frequency (hz)');
    ylabel('Time (s)');
    zlabel('Magnitude');
    axis([f1 f2 start_fft*step_t final_fft*step_t 0 a]);
    view([0,-1,0]);
    grid on;

    linkprop([ax_sx, ax_dx], {'CameraUpVector', 'CameraPosition', 'CameraTarget', 'XLim', 'YLim', 'ZLim'});
end


% ===== 2D plot =====
if plotGraphics >= 0
    pause;
    
    for i = start_fft:final_fft 
        figure(4);
        
        start_t = (i-1) * step_t;
        final_t = start_t + sec;
        ax_sx = subplot(1,2,1);
        title("Spectrum SX in [" + num2str(start_t) + " , " + num2str(final_t) + "] s");
        hold on;
        if plotSignals <= 0
            plot(f, S_sx(i,:), 'Color', [0 0.4470 0.7410]);
        end
        if plotSignals >= 0
            plot(f, S_f_sx(i,:), 'Color', [0.8500 0.3250 0.0980]);
        end
        if plotSignals == 0
            legend("Segnale originale", "Segnale filtrato");
        elseif plotSignals <= -1
            legend("Segnale originale");
        elseif plotSignals >= 1
            legend("Segnale filtrato");
        end
        ylabel('Magnitude');
        xlabel('Frequenxy (hz)');
        axis([f1 f2 0 a]);
        grid on;

        ax_dx = subplot(1,2,2);
        title("Spectrum DX in [" + num2str(start_t) + " , " + num2str(final_t) + "] s");
        hold on;
        if plotSignals <= 0
            plot(f, S_dx(i,:), 'Color', [0 0.4470 0.7410]);
        end
        if plotSignals >= 0
            plot(f, S_f_sx(i,:), 'Color', [0.8500 0.3250 0.0980]);
        end
        if plotSignals == 0
            legend("Segnale originale", "Segnale filtrato");
        elseif plotSignals <= -1
            legend("Segnale originale");
        elseif plotSignals >= 1
            legend("Segnale filtrato");
        end
        ylabel('Magnitude');
        xlabel('Frequenxy (hz)');
        axis([f1 f2 0 a]);
        grid on;

        linkaxes([ax_sx, ax_dx], 'x');

        pause;
        close;
    end
end