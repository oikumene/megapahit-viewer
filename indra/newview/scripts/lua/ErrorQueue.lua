-- ErrorQueue isa WaitQueue with the added feature that a producer can push an
-- error through the queue. Once that error is dequeued, every consumer will
-- raise that error.

local WaitQueue = require('WaitQueue')

ErrorQueue = WaitQueue:new()

function ErrorQueue:Error(message)
    -- Setting Error() is a marker, like closing the queue. Once we reach the
    -- error, every subsequent Dequeue() call will raise the same error.
    self._closed = message
    self:_wake_waiters()
end

function ErrorQueue:Dequeue()
    local value = WaitQueue.Dequeue(self)
    if value ~= nil then
        -- queue not yet closed, show caller
        return value
    end
    if self._closed == true then
        -- WaitQueue:close() sets true: queue has only been closed, tell caller
        return nil
    end
    -- self._closed is a message set by Error()
    error(self._closed)
end

return ErrorQueue
