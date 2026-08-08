import { NovaWebCore } from './core.js';

async function main() {
    // Khởi tạo thư viện thông qua tầng core (file 2)
    const client = new NovaWebCore({
        baseUrl: 'https://api.example.com',
        timeout: 5000,
        headers: { 'Content-Type': 'application/json' }
    });

    // Gắn bộ lọc yêu cầu mẫu
    client.api.addRequestInterceptor((config) => {
        console.log('Thư viện đang chuẩn bị gửi yêu cầu qua chuỗi module...');
        return config;
    });

    // Tiến hành kết nối và gọi API
    const status = await client.api.connect();
    console.log(status.message || status.error);

    const res = await client.get('/test');
    console.log('Phản hồi từ API:', res);
}

main();
