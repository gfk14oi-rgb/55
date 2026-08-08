import { ConnectionAPI } from './connection.js';

export class NovaWebCore {
    constructor(config) {
        // Gọi và khởi tạo tầng kết nối cơ sở từ file 1
        this.api = new ConnectionAPI(config);
    }

    async send(endpoint, options = {}) {
        let url = `${this.api.baseUrl}${endpoint}`;
        let config = {
            method: options.method || 'GET',
            headers: { ...this.api.defaultHeaders, ...options.headers },
            body: options.body ? JSON.stringify(options.body) : undefined
        };

        for (let interceptor of this.api.interceptors.request) {
            config = interceptor(config);
        }

        const controller = new AbortController();
        const timeoutId = setTimeout(() => controller.abort(), this.api.timeout);
        config.signal = controller.signal;

        try {
            const rawResponse = await fetch(url, config);
            clearTimeout(timeoutId);

            let data;
            const contentType = rawResponse.headers.get('content-type');
            if (contentType && contentType.includes('application/json')) {
                data = await rawResponse.json();
            } else {
                data = await rawResponse.text();
            }

            let result = {
                ok: rawResponse.ok,
                status: rawResponse.status,
                data: data
            };

            for (let interceptor of this.api.interceptors.response) {
                result = interceptor(result);
            }

            return result;
        } catch (error) {
            clearTimeout(timeoutId);
            return {
                ok: false,
                status: 500,
                error: error.name === 'AbortError' ? 'Yêu cầu quá thời gian (Timeout)' : error.message
            };
        }
    }

    get(endpoint, headers) {
        return this.send(endpoint, { method: 'GET', headers });
    }

    post(endpoint, body, headers) {
        return this.send(endpoint, { method: 'POST', body, headers });
    }
}
