# Qt GStreamer Kamera Entegrasyonu

*Bu belge Claude 3.7 Sonnet ile oluşturulmuştur.*

Bu proje, Qt ve GStreamer kullanarak kamera görüntüsünü yakalama ve görüntüleme işlemlerini gerçekleştirir. Temel olarak bir video akışını başlatma ve durdurma işlevselliği sağlar.

## Özellikler

- Kamera akışını başlatma
- Kamera akışını durdurma
- GStreamer komut satırı arayüzü (gst-launch) ile entegrasyon
- Hata yakalama ve loglama

## Gereksinimler

- Qt 5.x veya üzeri
- GStreamer 1.0 veya üzeri
- Windows, Linux veya macOS

## Kurulum

### GStreamer Kurulumu

1. [GStreamer web sitesinden](https://gstreamer.freedesktop.org/download/) işletim sisteminiz için uygun kurulum paketini indirin.
2. "Complete" kurulum seçeneğini seçerek GStreamer'ı yükleyin.
3. Kurulum tamamlandıktan sonra, GStreamer'ın bin dizinini sistem PATH değişkeninize ekleyin:
   - Windows: `C:\gstreamer\1.0\mingw_x86_64\bin` veya kurulumunuza göre uygun dizin
   - Linux/macOS: Genellikle otomatik olarak eklenir

### Projeyi Derleme

1. Qt Creator'ı açın
2. Projeyi açın
3. Projeyi derleyin (Ctrl+B veya Build menüsünden)

## Kullanım

Uygulama başlatıldığında:

1. "Başlat" butonuna tıklayarak kamera akışını başlatın
2. "Durdur" butonuna tıklayarak kamera akışını durdurun
3. Konsol çıktısında hata ve log mesajlarını görüntüleyin

## Kod Açıklaması

Proje, GStreamer'ı QProcess kullanarak çalıştırır. Ana kod parçaları şunlardır:

### Kamera Akışını Başlatma

```cpp
void MainWindow::startStream()
{
    // Kamera akışını başlatma kodu
    QString gstPath = "C:/gstreamer/1.0/mingw_x86_64/bin/gst-launch-1.0.exe";
    QStringList arguments;
    arguments << "-v" << "autovideosrc" << "!" << "videoconvert" << "!" << "autovideosink";
    gstProcess->start(gstPath, arguments);
}
```

### Kamera Akışını Durdurma

```cpp
void MainWindow::stopStream()
{
    // Kamera akışını durdurma kodu
    gstProcess->terminate();
    if (!gstProcess->waitForFinished(2000)) {
        gstProcess->kill();
    }
}
```

## Sorun Giderme

### "gst-launch-1.0 is not recognized" Hatası

Bu hata, GStreamer'ın PATH'de bulunamadığını gösterir. Çözüm için:

1. GStreamer'ın tam yolunu kodda belirtin:
   ```cpp
   QString gstPath = "C:/gstreamer/1.0/mingw_x86_64/bin/gst-launch-1.0.exe";
   ```

2. PATH değişkenini kontrol edin:
   - Komut isteminde `echo %PATH%` yazarak PATH içeriğini görüntüleyin
   - GStreamer'ın bin dizininin PATH'de olduğundan emin olun

3. Sistemi yeniden başlatın ve tekrar deneyin

### GStreamer Başlatılamadı Hatası

Bu hata, GStreamer uygulamasının başlatılamadığını gösterir. Çözüm için:

1. GStreamer yüklü olduğundan emin olun
2. GStreamer'ın tam yolunu doğru belirttiğinizden emin olun
3. Kamera donanımının çalışır durumda olduğundan emin olun
4. Farklı GStreamer pipeline parametreleri deneyin

## Lisans

Bu proje [MIT Lisansı](LICENSE) altında lisanslanmıştır.

## Katkıda Bulunma

1. Bu depoyu fork edin
2. Özellik dalınızı oluşturun (`git checkout -b yeni-ozellik`)
3. Değişikliklerinizi commit edin (`git commit -am 'Yeni özellik: açıklama'`)
4. Dalınızı push edin (`git push origin yeni-ozellik`)
5. Bir Pull Request oluşturun
