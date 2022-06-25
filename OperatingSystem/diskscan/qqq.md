qqq

<h1><a id="_0"></a>时间片轮转调度</h1>
<p>https://github.com/SKPrimin/HomeWork/tree/main/OperatingSystem/priority_rr/rr</p>
<blockquote>
<p>时间片轮转调度策略：在轮转(RR)法中，系统将所有的就绪进程按FCFS策略排成一个就绪队列。系统可设置每隔一定时间(如30 ms)便产生一次中断，去激活进程调度程序进行调度，把CPU分配给队首进程，并令其执行一个时间片。当它运行完毕后，又把处理机分配给就绪队列中新的队首进程，也让它执行一个时间片。这样，就可以保证就绪队列中的所有进程在确定的时间段内，都能获得一个时间片的处理机时间。</p>
</blockquote>
<h4><a id="_5"></a>数据结构和符号说明</h4>
<p>本次的PCB类数据结构有三个公共变量，五个私有变量，一个标志变量，以及一个时时返回给调度函数值的交互式变量。</p>
<pre><code class="prism language-java"><span class="token comment">//三个公共变量:作业名、到达时间、服务时间</span>
<span class="token class-name">String</span> threadName<span class="token punctuation">;</span> <span class="token keyword">int</span> timeArrival<span class="token punctuation">;</span> <span class="token keyword">int</span> timeSever<span class="token punctuation">;</span>
<span class="token comment">//五个私有变量：计算专用服务时间、开始执行时间、完成时间、周转时间、带权周转时间</span>
<span class="token keyword">private</span> <span class="token keyword">int</span> timeSeverFor<span class="token punctuation">;</span> <span class="token keyword">private</span> <span class="token keyword">int</span> timeStart<span class="token punctuation">;</span> <span class="token keyword">private</span> <span class="token keyword">int</span> timeComplete<span class="token punctuation">;</span>
<span class="token keyword">private</span> <span class="token keyword">int</span> timeTurnaround<span class="token punctuation">;</span> <span class="token keyword">private</span> <span class="token keyword">double</span> timeWeightedTurnaround<span class="token punctuation">;</span>
<span class="token comment">//一个标志：表示是否还需要调度 一个交互式变量：表示自己本次使用了多少时间</span>
<span class="token keyword">private</span> <span class="token keyword">boolean</span> isFinish <span class="token operator">=</span> <span class="token boolean">false</span><span class="token punctuation">;</span> <span class="token keyword">private</span> <span class="token keyword">int</span> timeUse<span class="token punctuation">;</span>
</code></pre>
<p>另有setter、getter函数实现私有变量的访问，同时有一个<code>public boolean isNotStart() { return timeStart == 0; }</code>函数根据进程的开始时间是否为0判断本程序是否启动过。在计算完成时间时，通过timeSever进行判断。每次时间片执行时都会时timeSever减去相应时间，此处的timeSever是时时更新的剩余服务时间，如果在一个时间片内提前结束了，则完成时间以及本次进程使用的时间都会进行调整，具体实现是通过三元运算符实现<code>timeSever -= timeSlice; timeComplete = timeSever &gt; 0 ? timeNow + timeSlice : timeNow + timeSlice + timeSever; timeUse = timeSever &gt;= 0 ? timeSlice : timeSlice + timeSever;</code>，而也只有在剩余服务时间&lt;=0时即本进程已完成才会进行周转时间等计算。</p>
<p>RR类进行系统调度时，由主机记录时间，并按照个一个轮转片内进程实际使用的时间累加，调用时只需按照到达时间排序一次就好，随后便是各时间片轮转，使用一个<code>while (countFinish &lt; num)</code>表示只要有一个进程未完成都会继续执行循环，而在while循环内部刚好是一个for each循环，各进程按照顺序一一轮转，如果进程未完成，则会调度此进程，完成就countFinish加1。调度时如果是第一次启动还需赋启动时间初值，随后运行本轮次<code>pcb.run(timeNow, timeSlice)</code>，记录下这次实际使用的时间并累加到当前时间上。</p>
<p>测试类Test包含一个主函数用于启动并时间片长度q，以及一个专门用于接受输入进程信息的函数。并且输入的进程数组在测试类中定义，也能实现在RR类中的函数直接更改进程的信息。</p>
<h4><a id="_25"></a>流程图</h4>
<p><img src="https://img-blog.csdnimg.cn/a6d184e168f54c5097e72e90c34df940.png#pic_center" alt="在这里插入图片描述" /></p>
<h4><a id="_36"></a>源程序</h4>
<h6><a id="PCB_38"></a>PCB类</h6>
<pre><code class="prism language-java"><span class="token keyword">import</span> <span class="token namespace">java<span class="token punctuation">.</span>text<span class="token punctuation">.</span></span><span class="token class-name">DecimalFormat</span><span class="token punctuation">;</span>

<span class="token keyword">public</span> <span class="token keyword">class</span> PCB <span class="token punctuation">{<!-- --></span>
    <span class="token comment">/**
     * 三个公共变量:作业名、到达时间、服务时间
     */</span>
    <span class="token class-name">String</span> threadName<span class="token punctuation">;</span>
    <span class="token keyword">int</span> timeArrival<span class="token punctuation">;</span>
    <span class="token keyword">int</span> timeSever<span class="token punctuation">;</span>

    <span class="token comment">/**
     * 五个私有变量：计算专用服务时间、开始执行时间、完成时间、周转时间、带权周转时间
     * 一个标志：表示是否还需要调度
     * 一个交互式变量：表示自己本次使用了多少时间
     */</span>
    <span class="token keyword">private</span> <span class="token keyword">int</span> timeSeverFor<span class="token punctuation">;</span>
    <span class="token keyword">private</span> <span class="token keyword">int</span> timeStart<span class="token punctuation">;</span>
    <span class="token keyword">private</span> <span class="token keyword">int</span> timeComplete<span class="token punctuation">;</span>
    <span class="token keyword">private</span> <span class="token keyword">int</span> timeTurnaround<span class="token punctuation">;</span>
    <span class="token keyword">private</span> <span class="token keyword">double</span> timeWeightedTurnaround<span class="token punctuation">;</span>
    <span class="token keyword">private</span> <span class="token keyword">boolean</span> isFinish <span class="token operator">=</span> <span class="token boolean">false</span><span class="token punctuation">;</span>
    <span class="token keyword">private</span> <span class="token keyword">int</span> timeUse<span class="token punctuation">;</span>
    
    <span class="token keyword">public</span> <span class="token function">PCB</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span><span class="token comment">//允许空参构造器存在</span>
    <span class="token punctuation">}</span>
    
    <span class="token keyword">public</span> <span class="token function">PCB</span><span class="token punctuation">(</span><span class="token class-name">String</span> threadName<span class="token punctuation">,</span> <span class="token keyword">int</span> timeArrival<span class="token punctuation">,</span> <span class="token keyword">int</span> timeSever<span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span> <span class="token comment">//正规的有参构造器</span>
        <span class="token keyword">this</span><span class="token punctuation">.</span>threadName <span class="token operator">=</span> threadName<span class="token punctuation">;</span>
        <span class="token keyword">this</span><span class="token punctuation">.</span>timeArrival <span class="token operator">=</span> timeArrival<span class="token punctuation">;</span>
        <span class="token keyword">this</span><span class="token punctuation">.</span>timeSever <span class="token operator">=</span> timeSever<span class="token punctuation">;</span>
        <span class="token keyword">this</span><span class="token punctuation">.</span>timeSeverFor <span class="token operator">=</span> timeSever<span class="token punctuation">;</span>
    <span class="token punctuation">}</span>
    
    <span class="token keyword">public</span> <span class="token keyword">void</span> <span class="token function">setTimeStart</span><span class="token punctuation">(</span><span class="token keyword">int</span> timeStart<span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span><span class="token comment">//将由算法调度程序分配开始时间</span>
        <span class="token keyword">this</span><span class="token punctuation">.</span>timeStart <span class="token operator">=</span> timeStart<span class="token punctuation">;</span>
    <span class="token punctuation">}</span>
    
    <span class="token keyword">public</span> <span class="token keyword">boolean</span> <span class="token function">isNotStart</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span>
        <span class="token keyword">return</span> timeStart <span class="token operator">==</span> <span class="token number">0</span><span class="token punctuation">;</span>
    <span class="token punctuation">}</span>
    
    <span class="token keyword">public</span> <span class="token keyword">int</span> <span class="token function">getTimeTurnaround</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span>
        <span class="token keyword">return</span> timeTurnaround<span class="token punctuation">;</span>
    <span class="token punctuation">}</span>
    
    <span class="token keyword">public</span> <span class="token keyword">double</span> <span class="token function">getTimeWeightedTurnaround</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span>
        <span class="token keyword">return</span> timeWeightedTurnaround<span class="token punctuation">;</span>
    <span class="token punctuation">}</span>
    
    <span class="token keyword">public</span> <span class="token keyword">boolean</span> <span class="token function">isFinish</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span>
        <span class="token keyword">return</span> isFinish<span class="token punctuation">;</span>
    <span class="token punctuation">}</span>
    
    <span class="token keyword">public</span> <span class="token keyword">int</span> <span class="token function">getTimeUse</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span>
        <span class="token keyword">return</span> timeUse<span class="token punctuation">;</span>
    <span class="token punctuation">}</span>
    
    <span class="token keyword">public</span> <span class="token keyword">void</span> <span class="token function">run</span><span class="token punctuation">(</span><span class="token keyword">int</span> timeNow<span class="token punctuation">,</span> <span class="token keyword">int</span> timeSlice<span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span> <span class="token comment">//开始调度后的运行内容</span>
        <span class="token comment">/*计算完成时间*/</span>
        <span class="token keyword">if</span> <span class="token punctuation">(</span>timeSever <span class="token operator">&gt;</span> <span class="token number">0</span><span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span>
            timeSever <span class="token operator">-=</span> timeSlice<span class="token punctuation">;</span>
            <span class="token comment">// 此处保证进程在时间片内提前完成的情况下，依然能准确算出完成时间，并返回正确的使用时间</span>
            timeComplete <span class="token operator">=</span> timeSever <span class="token operator">&gt;</span> <span class="token number">0</span> <span class="token operator">?</span> timeNow <span class="token operator">+</span> timeSlice <span class="token operator">:</span> timeNow <span class="token operator">+</span> timeSlice <span class="token operator">+</span> timeSever<span class="token punctuation">;</span>
            timeUse <span class="token operator">=</span> timeSever <span class="token operator">&gt;=</span> <span class="token number">0</span> <span class="token operator">?</span> timeSlice <span class="token operator">:</span> timeSlice <span class="token operator">+</span> timeSever<span class="token punctuation">;</span>
        <span class="token punctuation">}</span>
        <span class="token comment">/* 当本次进程完成时，计算周转时间、带权周转时间 */</span>
        <span class="token keyword">if</span> <span class="token punctuation">(</span>timeSever <span class="token operator">&lt;=</span> <span class="token number">0</span><span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span>
            isFinish <span class="token operator">=</span> <span class="token boolean">true</span><span class="token punctuation">;</span>
            timeTurnaround <span class="token operator">=</span> timeComplete <span class="token operator">-</span> timeArrival<span class="token punctuation">;</span>
            <span class="token class-name">DecimalFormat</span> dF <span class="token operator">=</span> <span class="token keyword">new</span> <span class="token class-name">DecimalFormat</span><span class="token punctuation">(</span><span class="token string">"0.00"</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
            timeWeightedTurnaround <span class="token operator">=</span> <span class="token class-name">Double</span><span class="token punctuation">.</span><span class="token function">parseDouble</span><span class="token punctuation">(</span>dF<span class="token punctuation">.</span><span class="token function">format</span><span class="token punctuation">(</span><span class="token punctuation">(</span><span class="token keyword">double</span><span class="token punctuation">)</span> timeTurnaround <span class="token operator">/</span> timeSeverFor<span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
            <span class="token comment">//调用toString()将内容输出</span>
            <span class="token class-name">System</span><span class="token punctuation">.</span>out<span class="token punctuation">.</span><span class="token function">println</span><span class="token punctuation">(</span><span class="token keyword">this</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
        <span class="token punctuation">}</span>
    <span class="token punctuation">}</span>
    
    <span class="token annotation punctuation">@Override</span>
    <span class="token keyword">public</span> <span class="token class-name">String</span> <span class="token function">toString</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span>
        <span class="token keyword">return</span> <span class="token string">"'"</span> <span class="token operator">+</span> threadName <span class="token operator">+</span> <span class="token string">'\''</span> <span class="token operator">+</span>
                <span class="token string">"\t\t"</span> <span class="token operator">+</span> timeArrival <span class="token operator">+</span>
                <span class="token string">"\t\t"</span> <span class="token operator">+</span> timeSeverFor <span class="token operator">+</span>
                <span class="token string">"\t\t\t"</span> <span class="token operator">+</span> timeStart <span class="token operator">+</span>
                <span class="token string">"\t\t"</span> <span class="token operator">+</span> timeComplete <span class="token operator">+</span>
                <span class="token string">"\t\t"</span> <span class="token operator">+</span> timeTurnaround <span class="token operator">+</span>
                <span class="token string">"\t\t"</span> <span class="token operator">+</span> timeWeightedTurnaround<span class="token punctuation">;</span>
    <span class="token punctuation">}</span>
<span class="token punctuation">}</span>
</code></pre>
<h6><a id="RR_130"></a>RR类</h6>
<pre><code class="prism language-java"><span class="token keyword">public</span> <span class="token keyword">class</span> RR <span class="token punctuation">{<!-- --></span>
    <span class="token keyword">public</span> <span class="token keyword">void</span> <span class="token function">dispatch</span><span class="token punctuation">(</span>PCB<span class="token punctuation">[</span><span class="token punctuation">]</span> pcbarr<span class="token punctuation">,</span> <span class="token keyword">int</span> timeSlice<span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span>
        <span class="token class-name">System</span><span class="token punctuation">.</span>out<span class="token punctuation">.</span><span class="token function">println</span><span class="token punctuation">(</span><span class="token string">"作业名\t到达时间\t服务时间\t开始执行时间\t完成时间\t周转时间\t带权周转时间"</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
        <span class="token keyword">int</span> num <span class="token operator">=</span> pcbarr<span class="token punctuation">.</span>length<span class="token punctuation">;</span>
        <span class="token comment">//由主机记录当前时间，以便实现时间片轮转</span>
        <span class="token keyword">int</span> timeNow <span class="token operator">=</span> <span class="token number">0</span><span class="token punctuation">;</span>
        <span class="token function">sort</span><span class="token punctuation">(</span>pcbarr<span class="token punctuation">,</span> num<span class="token punctuation">)</span><span class="token punctuation">;</span>
        <span class="token comment">//此后的PCB数组都是依照到达时间排序完成的</span>
        <span class="token keyword">int</span> countFinish <span class="token operator">=</span> <span class="token number">0</span><span class="token punctuation">;</span>
        <span class="token keyword">while</span> <span class="token punctuation">(</span>countFinish <span class="token operator">&lt;</span> num<span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span>
            countFinish <span class="token operator">=</span> <span class="token number">0</span><span class="token punctuation">;</span>
            <span class="token keyword">for</span> <span class="token punctuation">(</span>PCB pcb <span class="token operator">:</span> pcbarr<span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span>
                <span class="token comment">//如果此进程未完成，且时间已到达，则会给该进程一个时间片,否则进行下一个</span>
                <span class="token keyword">if</span> <span class="token punctuation">(</span>timeNow <span class="token operator">&gt;=</span> pcb<span class="token punctuation">.</span>timeArrival<span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span>
                    <span class="token keyword">if</span> <span class="token punctuation">(</span><span class="token punctuation">(</span><span class="token operator">!</span>pcb<span class="token punctuation">.</span><span class="token function">isFinish</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span>
                        <span class="token keyword">if</span> <span class="token punctuation">(</span>pcb<span class="token punctuation">.</span><span class="token function">isNotStart</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span>
                            pcb<span class="token punctuation">.</span><span class="token function">setTimeStart</span><span class="token punctuation">(</span>timeNow<span class="token punctuation">)</span><span class="token punctuation">;</span>
                        <span class="token punctuation">}</span>
                        pcb<span class="token punctuation">.</span><span class="token function">run</span><span class="token punctuation">(</span>timeNow<span class="token punctuation">,</span> timeSlice<span class="token punctuation">)</span><span class="token punctuation">;</span>
                        timeNow <span class="token operator">+=</span> pcb<span class="token punctuation">.</span><span class="token function">getTimeUse</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
                    <span class="token punctuation">}</span> <span class="token keyword">else</span> <span class="token punctuation">{<!-- --></span>
                        countFinish<span class="token operator">++</span><span class="token punctuation">;</span>
                    <span class="token punctuation">}</span>
                <span class="token punctuation">}</span><span class="token keyword">else</span><span class="token punctuation">{<!-- --></span><span class="token comment">//若还未到，进行下一轮，没有需要调度的进程则直接当前时间加一</span>
                    <span class="token keyword">if</span><span class="token punctuation">(</span>pcb<span class="token punctuation">.</span><span class="token function">isFinish</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">{<!-- --></span>
                    	timeNow<span class="token operator">++</span><span class="token punctuation">;</span>
                    <span class="token punctuation">}</span>
                    <span class="token keyword">break</span><span class="token punctuation">;</span>
                <span class="token punctuation">}</span>
            <span class="token punctuation">}</span>
        <span class="token punctuation">}</span>
        <span class="token comment">//周转时间之和与带权周转时间之和</span>
        <span class="token keyword">int</span> timeTurnaroundSum <span class="token operator">=</span> <span class="token number">0</span><span class="token punctuation">;</span>
        <span class="token keyword">double</span> timeWeightedTurnaroundSum <span class="token operator">=</span> <span class="token number">0</span><span class="token punctuation">;</span>
        <span class="token keyword">for</span> <span class="token punctuation">(</span>PCB pcb <span class="token operator">:</span> pcbarr<span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span>
            timeTurnaroundSum <span class="token operator">+=</span> pcb<span class="token punctuation">.</span><span class="token function">getTimeTurnaround</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
            timeWeightedTurnaroundSum <span class="token operator">+=</span> pcb<span class="token punctuation">.</span><span class="token function">getTimeWeightedTurnaround</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
        <span class="token punctuation">}</span>
        <span class="token class-name">System</span><span class="token punctuation">.</span>out<span class="token punctuation">.</span><span class="token function">println</span><span class="token punctuation">(</span><span class="token string">"平均周转时间："</span> <span class="token operator">+</span> <span class="token punctuation">(</span><span class="token keyword">double</span><span class="token punctuation">)</span> timeTurnaroundSum <span class="token operator">/</span> num <span class="token operator">+</span>
                <span class="token string">"，平均带权周转时间："</span> <span class="token operator">+</span> timeWeightedTurnaroundSum <span class="token operator">/</span> num<span class="token punctuation">)</span><span class="token punctuation">;</span>
    <span class="token punctuation">}</span>

    <span class="token keyword">public</span> <span class="token keyword">void</span> <span class="token function">sort</span><span class="token punctuation">(</span>PCB<span class="token punctuation">[</span><span class="token punctuation">]</span> arr<span class="token punctuation">,</span> <span class="token keyword">int</span> num<span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span>
        <span class="token comment">//根据到达时间对作业进行升序排序，排序方式：选择排序</span>
        <span class="token keyword">for</span> <span class="token punctuation">(</span><span class="token keyword">int</span> i <span class="token operator">=</span> <span class="token number">0</span><span class="token punctuation">;</span> i <span class="token operator">&lt;</span> num <span class="token operator">-</span> <span class="token number">1</span><span class="token punctuation">;</span> i<span class="token operator">++</span><span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span>
            <span class="token keyword">int</span> index <span class="token operator">=</span> i<span class="token punctuation">;</span>
            <span class="token keyword">for</span> <span class="token punctuation">(</span><span class="token keyword">int</span> j <span class="token operator">=</span> i <span class="token operator">+</span> <span class="token number">1</span><span class="token punctuation">;</span> j <span class="token operator">&lt;</span> num<span class="token punctuation">;</span> j<span class="token operator">++</span><span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span>
                <span class="token keyword">if</span> <span class="token punctuation">(</span>arr<span class="token punctuation">[</span>j<span class="token punctuation">]</span><span class="token punctuation">.</span>timeArrival <span class="token operator">&lt;</span> arr<span class="token punctuation">[</span>index<span class="token punctuation">]</span><span class="token punctuation">.</span>timeArrival<span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span>
                    index <span class="token operator">=</span> j<span class="token punctuation">;</span>
                <span class="token punctuation">}</span>
            <span class="token punctuation">}</span>
            <span class="token comment">//将找到的最小值放到第一的位置，进行下一遍循环</span>
            <span class="token class-name">PCB</span> temp <span class="token operator">=</span> arr<span class="token punctuation">[</span>index<span class="token punctuation">]</span><span class="token punctuation">;</span>
            arr<span class="token punctuation">[</span>index<span class="token punctuation">]</span> <span class="token operator">=</span> arr<span class="token punctuation">[</span>i<span class="token punctuation">]</span><span class="token punctuation">;</span>
            arr<span class="token punctuation">[</span>i<span class="token punctuation">]</span> <span class="token operator">=</span> temp<span class="token punctuation">;</span>
        <span class="token punctuation">}</span>
    <span class="token punctuation">}</span>
<span class="token punctuation">}</span>
</code></pre>
<h6><a id="Test_193"></a>Test类</h6>
<pre><code class="prism language-java"><span class="token keyword">import</span> <span class="token namespace">java<span class="token punctuation">.</span>util<span class="token punctuation">.</span></span><span class="token class-name">Scanner</span><span class="token punctuation">;</span>

<span class="token keyword">public</span> <span class="token keyword">class</span> <span class="token class-name">Test</span> <span class="token punctuation">{<!-- --></span>
    <span class="token keyword">public</span> <span class="token keyword">static</span> <span class="token keyword">void</span> <span class="token function">main</span><span class="token punctuation">(</span><span class="token class-name">String</span><span class="token punctuation">[</span><span class="token punctuation">]</span> args<span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span>
        <span class="token comment">// 设置时间片长度</span>
        <span class="token class-name">System</span><span class="token punctuation">.</span>out<span class="token punctuation">.</span><span class="token function">print</span><span class="token punctuation">(</span><span class="token string">"时间片轮转算法\n请设置时间片长度q = "</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
        <span class="token class-name">Scanner</span> sc <span class="token operator">=</span> <span class="token keyword">new</span> <span class="token class-name">Scanner</span><span class="token punctuation">(</span><span class="token class-name">System</span><span class="token punctuation">.</span>in<span class="token punctuation">)</span><span class="token punctuation">;</span>
        <span class="token keyword">int</span> timeSlice <span class="token operator">=</span> sc<span class="token punctuation">.</span><span class="token function">nextInt</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
        <span class="token comment">// 读取输入的数组</span>
        PCB<span class="token punctuation">[</span><span class="token punctuation">]</span> arr1 <span class="token operator">=</span> <span class="token function">dataReadIn</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
        <span class="token comment">//调用时间片轮转算法</span>
        <span class="token class-name">RR</span> rr <span class="token operator">=</span> <span class="token keyword">new</span> <span class="token function">RR</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
        rr<span class="token punctuation">.</span><span class="token function">dispatch</span><span class="token punctuation">(</span>arr1<span class="token punctuation">,</span> timeSlice<span class="token punctuation">)</span><span class="token punctuation">;</span>
    <span class="token punctuation">}</span>

    <span class="token keyword">public</span> <span class="token keyword">static</span> PCB<span class="token punctuation">[</span><span class="token punctuation">]</span> <span class="token function">dataReadIn</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span> <span class="token comment">//数据读入函数,直接设为静态函数，强制要求写入数据</span>
        <span class="token class-name">System</span><span class="token punctuation">.</span>out<span class="token punctuation">.</span><span class="token function">print</span><span class="token punctuation">(</span><span class="token string">"请输入本次需要调度的作业数目："</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
        <span class="token class-name">Scanner</span> sc <span class="token operator">=</span> <span class="token keyword">new</span> <span class="token class-name">Scanner</span><span class="token punctuation">(</span><span class="token class-name">System</span><span class="token punctuation">.</span>in<span class="token punctuation">)</span><span class="token punctuation">;</span>
        <span class="token keyword">int</span> n <span class="token operator">=</span> sc<span class="token punctuation">.</span><span class="token function">nextInt</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
        PCB<span class="token punctuation">[</span><span class="token punctuation">]</span> starr <span class="token operator">=</span> <span class="token keyword">new</span> PCB<span class="token punctuation">[</span>n<span class="token punctuation">]</span><span class="token punctuation">;</span>
        <span class="token class-name">System</span><span class="token punctuation">.</span>out<span class="token punctuation">.</span><span class="token function">println</span><span class="token punctuation">(</span><span class="token string">"请输入每一个作业的作业名、到达时间、服务时间（一行一个,中间用空格区分）"</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
        <span class="token keyword">for</span> <span class="token punctuation">(</span><span class="token keyword">int</span> i <span class="token operator">=</span> <span class="token number">0</span><span class="token punctuation">;</span> i <span class="token operator">&lt;</span> n<span class="token punctuation">;</span> i<span class="token operator">++</span><span class="token punctuation">)</span> <span class="token punctuation">{<!-- --></span>
            starr<span class="token punctuation">[</span>i<span class="token punctuation">]</span> <span class="token operator">=</span> <span class="token keyword">new</span> <span class="token function">PCB</span><span class="token punctuation">(</span>sc<span class="token punctuation">.</span><span class="token function">next</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">,</span> sc<span class="token punctuation">.</span><span class="token function">nextInt</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">,</span> sc<span class="token punctuation">.</span><span class="token function">nextInt</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
        <span class="token punctuation">}</span>
        <span class="token keyword">return</span> starr<span class="token punctuation">;</span>
    <span class="token punctuation">}</span>
<span class="token punctuation">}</span>
</code></pre>
<h4><a id="_225"></a>运行时的初值和结果</h4>
<blockquote>
<p>时间片轮转算法<br /> 请设置时间片长度q = 1<br /> 请输入本次需要调度的作业数目：5<br /> 请输入每一个作业的作业名、到达时间、服务时间（一行一个,中间用空格区分）<br /> A 0 4<br /> B 1 3<br /> C 2 4<br /> D 3 2<br /> E 4 4<br /> 作业名 到达时间 服务时间 开始执行时间 完成时间 周转时间 带权周转时间<br /> &lsquo;D&rsquo; 3 2 3 9 6 3.0<br /> &lsquo;B&rsquo; 1 3 1 12 11 3.67<br /> &lsquo;A&rsquo; 0 4 5 15 15 3.75<br /> &lsquo;C&rsquo; 2 4 2 16 14 3.5<br /> &lsquo;E&rsquo; 4 4 4 17 13 3.25<br /> 平均周转时间：11.8，平均带权周转时间：3.434</p>
<p>时间片轮转算法<br /> 请设置时间片长度q = 4<br /> 请输入本次需要调度的作业数目：5<br /> 请输入每一个作业的作业名、到达时间、服务时间（一行一个,中间用空格区分）<br /> A 0 4<br /> B 1 3<br /> C 2 4<br /> D 3 2<br /> E 4 4<br /> 作业名 到达时间 服务时间 开始执行时间 完成时间 周转时间 带权周转时间<br /> &lsquo;A&rsquo; 0 4 0 4 4 1.0<br /> &lsquo;B&rsquo; 1 3 4 7 6 2.0<br /> &lsquo;C&rsquo; 2 4 7 11 9 2.25<br /> &lsquo;D&rsquo; 3 2 11 13 10 5.0<br /> &lsquo;E&rsquo; 4 4 13 17 13 3.25<br /> 平均周转时间：8.4，平均带权周转时间：2.7</p>

</blockquote>
<p>与理想状态相同<br /> <img alt="image-20211118235513791" /><img alt="image-20211118235548720" /></p>
<hr />
<p><img src="https://img-blog.csdnimg.cn/12b7826368924d4a8e1ac2a46b44830a.png#pic_center" alt="在这里插入图片描述" /></p>
<p><img src="https://img-blog.csdnimg.cn/71b878c6198c4ff4bb261d5229fd9726.png#pic_center" alt="在这里插入图片描述" /></p>
<p>&nbsp;</p>