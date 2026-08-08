export class ConnectionAPI {
    constructor(config = {}) {
        this.baseUrl = config.baseUrl || '';
        this.defaultHeaders = config.headers || { 'Content-Type': 'application/json' };
        this.timeout = config.timeout || 10000;
        this.status = 'DISCONNECTED';
        this.interceptors = {
            request: [],
            response: []
        };
    }

    addRequestInterceptor(fn) {
        this.interceptors.request.push(fn);
    }

    addResponseInterceptor(fn) {
        this.interceptors.response.push(fn);
    }

    async connect() {
        this.status = 'CONNECTING';
        try {
            const response = await fetch(`${this.baseUrl}/ping`, { method: 'GET' });
            if (response.ok) {
                this.status = 'CONNECTED';
                return { success: true, message: 'Kết nối API thành công.' };
            } else {
                this.status = 'DISCONNECTED';
                throw new Error('Không thể thiết lập kết nối tới máy chủ.');
            }
        } catch (error) {
            this.status = 'DISCONNECTED';
            return { success: false, error: error.message };
        }
    }

    disconnect() {
        this.status = 'DISCONNECTED';
        return { success: true, message: 'Đã ngắt kết nối API.' };
    }
}
