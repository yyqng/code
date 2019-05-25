#!/usr/bin/python
#tensorflow
def tf_001():
     hello = tf.constant('Hello, tensorflow!')
     sess = tf.Session()
     print sess.run(hello)

#tensorflow
def tf_002():
    import numpy as np
    #1. define TensorFlow const and variable
    const = tf.constant(2.0, name='const')
    b = tf.placeholder(tf.float32, [None, 1], name='b') # creat placeholder
    #b = tf.Variable(2.0, name='c')
    c = tf.Variable(1.0, dtype=tf.float32, name='c')    # dtype : Optional
    #2. creat operation
    d = tf.add(b, c, name='d')
    e = tf.add(c, const, name='e')
    a = tf.multiply(d, e, name='a')
    #3. define init operation
    init_op = tf.global_variables_initializer()
    #4. creat a session
    with tf.Session() as sess:
            writer = tf.summary.FileWriter("logs/", sess.graph)
            sess.run(init_op)
            a_out = sess.run(a, feed_dict={b: np.arange(0, 10)[:, np.newaxis]})
            #a_out = sess.run(a)
            print("Variable a is {}".format(a_out))

#tensorboard usage : tensorboard --logdir logs . Then use chrome to open the link.
def tb_003():
    with tf.name_scope('graph') as scope:
            matrix1 = tf.constant([[3., 3.]],name ='matrix1')  #1 row by 2 column
            matrix2 = tf.constant([[2.],[2.]],name ='matrix2') #2 row by 1 column
            product = tf.matmul(matrix1, matrix2,name='product')
    sess = tf.Session()
    writer = tf.summary.FileWriter("logs/", sess.graph)
    init = tf.global_variables_initializer()
    sess.run(init)

#Neural Network
def neural_004():
    #1. load data
    from tensorflow.examples.tutorials.mnist import input_data
    mnist = input_data.read_data_sets("MNIST_data/", one_hot=True)
    #2. define hyper parameters and placeholder
    learning_rate = 0.5
    epochs = 10
    batch_size = 100

    # placeholder
    # input picture : 28 x 28  = 784
    x = tf.placeholder(tf.float32, [None, 784])
    # output: 0-9 one-hot
    y = tf.placeholder(tf.float32, [None, 10])
    
    #3. define w and b
    # hidden layer => w, b
    W1 = tf.Variable(tf.random_normal([784, 300], stddev=0.03), name='W1')
    b1 = tf.Variable(tf.random_normal([300]), name='b1')
    # output layer => w, b
    W2 = tf.Variable(tf.random_normal([300, 10], stddev=0.03), name='W2')
    b2 = tf.Variable(tf.random_normal([10]), name='b2')

    #4. Constructing hidden layer
    hidden_out = tf.add(tf.matmul(x, W1), b1)
    hidden_out = tf.nn.relu(hidden_out)

    #5. calculate output
    y_ = tf.nn.softmax(tf.add(tf.matmul(hidden_out, W2), b2))

    #6. BP : define loss
    y_clipped = tf.clip_by_value(y_, 1e-10, 0.9999999)
    cross_entropy = -tf.reduce_mean(tf.reduce_sum(y * tf.log(y_clipped) + (1 - y) * tf.log(1 - y_clipped), axis=1))

    #7. BP : Define optimization algorithm
    optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate).minimize(cross_entropy)

    #8. init operator
    init_op = tf.global_variables_initializer()

    #9. Define initialization operation and accuracy rate node
    correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(y_, 1))
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

    # creat session and setting up the trianing
    with tf.Session() as sess:
        writer = tf.summary.FileWriter("logs/", sess.graph)
        # init
        sess.run(init_op)
        total_batch = int(len(mnist.train.labels) / batch_size)
        for epoch in range(epochs):
            avg_cost = 0
            for i in range(total_batch):
                batch_x, batch_y = mnist.train.next_batch(batch_size=batch_size)
                _, c = sess.run([optimizer, cross_entropy], feed_dict={x: batch_x, y: batch_y})
                avg_cost += c / total_batch
            print("Epoch:", (epoch + 1), "cost = ", "{:.3f}".format(avg_cost))
        print(sess.run(accuracy, feed_dict={x: mnist.test.images, y: mnist.test.labels}))

def tf_005():
    a = tf.constant( [1.0,2.0],name="a")
    b = tf.constant( [2.0,3.0],name="b")
    result = a + b;
    sess = tf.Session()
    writer = tf.summary.FileWriter("logs/", sess.graph)
    print sess.run(result)
    print ( a.graph is tf.get_default_graph() )

def tf_006():
    g1 = tf.Graph()
    with g1.as_default():
        #Define v in g1
        v = tf.get_variable( "v", initializer=tf.zeros_initializer()(shape=[1]))

    #Read v of g1
    with tf.Session(graph=g1) as sess:
        tf.global_variables_initializer().run()
        with tf.variable_scope("", reuse=True):
            print (sess.run(tf.get_variable("v")))

    g2 = tf.Graph()
    with g2.as_default():
        #Define v in g2
        v = tf.get_variable( "v", initializer=tf.ones_initializer()(shape=[1]))

    #Read v of g2
    with tf.Session(graph=g2) as sess:
        tf.global_variables_initializer().run()
        with tf.variable_scope("", reuse=True):
            print (sess.run(tf.get_variable("v")))


def gpu_007():
    g = tf.Graph()
    a = tf.constant( [1.0,2.0],name="a")
    b = tf.constant( [2.0,3.0],name="b")
    with g.device('/gpu:0'):
        result = a + b;

    with tf.Session() as sess:
        tf.global_variables_initializer().run()
        print sess.run(result)

def tf_008():
    #mean=0(default value) stddev=2(standard deviation)
    #default type : tf.float32
    w1 = tf.Variable( tf.random_normal( [2,3] , stddev=1, seed=1 ))
    w2 = tf.Variable( tf.random_normal( [3,1] , stddev=1, seed=1 ))
    #x  = tf.constant( [[0.7, 0.9]] )
    #x  = tf.placeholder( tf.float32, [1,2], name="input")
    x  = tf.placeholder( tf.float32, [3,2], name="input")
    a  = tf.matmul( x , w1)
    y  = tf.matmul( a , w2)

    sess = tf.Session()

    init_op = tf.global_variables_initializer()
    sess.run( init_op )
    #The about two commands are equivalent to:
    #sess.run( w1.initializer )
    #sess.run( w2.initializer )

    #print ( sess.run(y) )
    print ( sess.run(y, feed_dict={x: [[0.7,0.9], [0.1,0.4], [0.5,0.8] ] }) )
    sess.close()

def tf_009():
    from numpy.random import RandomState
    batch_size = 8
    # mean=0(default value) stddev=2(standard deviation)
    w1 = tf.Variable( tf.random_normal( [2,3] , stddev=1, seed=1 ))
    w2 = tf.Variable( tf.random_normal( [3,1] , stddev=1, seed=1 ))
    x  = tf.placeholder( tf.float32, shape=(None,2), name='x-input')
    y_ = tf.placeholder( tf.float32, shape=(None,1), name='y-input')

    # Define forward propagation process
    a  = tf.matmul( x , w1)
    y  = tf.matmul( a , w2)

    # Define loss function and back-propagation algorithm
    cross_entropy = -tf.reduce_mean( y_ * tf.log( tf.clip_by_value(y,1e-10,1.0) ) )
    train_step = tf.train.AdamOptimizer(0.001).minimize( cross_entropy )

    rdm = RandomState(1)
    dataset_size = 128
    X = rdm.rand(dataset_size, 2)
    Y = [ [int (x1+x2) < 1] for (x1,x2) in X ]
    
    with tf.Session() as sess:
        init_op = tf.global_variables_initializer()
        sess.run( init_op )
        print ( sess.run(w1) )
        print ( sess.run(w2) )

        STEPS = 5000
        for i in range(STEPS):
            start = (i*batch_size) % dataset_size
            end = min(start+batch_size, dataset_size)
            sess.run(train_step, feed_dict={x: X[start:end] , y_: Y[start:end]} )
            if i%1000 == 0:
                total_cross_entropy = sess.run( cross_entropy , feed_dict={x:X, y_:Y})
                print("After %d steps trainning steps ,cross entropy on all data is %g " % (i ,total_cross_entropy))

        print ( sess.run(w1) )
        print ( sess.run(w2) )

import os
os.environ['TF_CPP_MIN_LOG_LEVEL']='2'
import tensorflow as tf

#tf_001();
#tf_002();
#tb_003();
#neural_004()
#tf_005();
#tf_006();
#gpu_007()
#tf_008();
tf_009();
