import serial
import tkinter as tk

# Función para enviar datos al puerto serial
def enviar_dato(numero):
    puerto_serie.write(str(numero).encode())

# Configuración de la comunicación serial
puerto_serie = serial.Serial('COM3', 9600)

# Funciones para enviar los números al presionar los botones
def enviar_100():
    enviar_dato(100)

def enviar_200():
    enviar_dato(200)

def enviar_300():
    enviar_dato(300)

# Función para leer datos del puerto serial
def leer_datos():
    try:
        if puerto_serie.in_waiting > 0:
            datos = puerto_serie.readline().decode().strip()
            if datos:
                procesar_datos(datos)
    except serial.SerialException:
        print("Error de comunicación serial")

# Función para procesar los datos recibidos
def procesar_datos(datos):
    if datos in ['10', '20', '30', '40']:
        cambiar_color_circulo(datos)
    else:
        actualizar_valor_potenciometro(datos)

# Función para cambiar el color de los círculos
def cambiar_color_circulo(num):
    if num == '10':
        canvas.itemconfig(circle1, fill="green")
    elif num == '20':
        canvas.itemconfig(circle2, fill="green")
    elif num == '30':
        canvas.itemconfig(circle3, fill="green")
    elif num == '40':
        canvas.itemconfig(circle1, fill="black")
        canvas.itemconfig(circle2, fill="black")
        canvas.itemconfig(circle3, fill="black")

# Función para actualizar el valor del potenciómetro en la interfaz
def actualizar_valor_potenciometro(valor):
    try:
        valor_float = float(valor)
        if valor_float <= 5.0:
            valor_potenciometro = valor_float * 80
            canvas.coords(rect, 260, 186 - valor_potenciometro * 0.5, 260 + 40, 190)
            etiqueta_valor.config(text="Valor del potenciómetro: " + valor)
    except ValueError:
        print("Error: no se pudo convertir el valor a float")

# Función para iniciar la lectura de datos del puerto serial
def iniciar_lectura():
    leer_datos()
    ventana.after(100, iniciar_lectura)

# Configuración de la ventana
ventana = tk.Tk()
ventana.title("Visualización de Potenciómetro y Control de LEDs")
ventana.geometry("555x400")

# Crear un lienzo para dibujar los elementos
canvas = tk.Canvas(ventana, width=555, height=300)
canvas.place(x=0, y=20)

# Crear un rectángulo inicialmente invisible
rect = canvas.create_rectangle(0, 0, 0, 0, fill="blue")

# Crear círculos iniciales
circle1 = canvas.create_oval(50, 250, 100, 300, fill="black")
circle2 = canvas.create_oval(250, 250, 300, 300, fill="black")
circle3 = canvas.create_oval(450, 250, 500, 300, fill="black")

# Variable para almacenar el valor del potenciómetro
valor_potenciometro = 0

# Etiqueta para mostrar el valor del potenciómetro
etiqueta_valor = tk.Label(ventana, text="Valor del potenciómetro: " + str(valor_potenciometro))
etiqueta_valor.place(x=200, y=220)

# Crear botones para enviar los números
boton_100 = tk.Button(ventana, text="Boton 1", command=enviar_100)
boton_100.place(x=47, y=350)

boton_200 = tk.Button(ventana, text="Boton 2", command=enviar_200)
boton_200.place(x=247, y=350)

boton_300 = tk.Button(ventana, text="Boton 3", command=enviar_300)
boton_300.place(x=447, y=350)

# Iniciar la lectura de datos del puerto serial
iniciar_lectura()

# Ejecutar el bucle principal de la interfaz gráfica
ventana.mainloop()

